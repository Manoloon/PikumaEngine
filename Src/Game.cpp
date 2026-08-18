//
// Created by Manoloon on 13/05/2022.
//
#include "imgui-SFML.h"
#include "imgui.h"

#include "Game.h"
#include "GameGlobals.h"
#include "ECS/ECS.h"
#include "ECS/AssetStore.h"
#include "Systems/SMovement.h"
#include "Systems/SRender.h"
#include "Systems/SAnimation.h"
#include "Systems/SCollision.h"
#include "Systems/SInput.h"
#include "Systems/SRenderDebugGUI.h"
#include "Systems/SDamage.h"
#include "Systems/SCamera.h"
#include "Systems/SProjectileEmitter.h"
#include "Systems/SDebugRender.h"
#include "LevelLoader.h"

float Game::mapWidth;
float Game::mapHeight;

Game::Game()
{
    registry = std::make_unique<Registry>();
    assetStore = std::make_unique<AssetStore>();
    eventBus = std::make_unique<EventBus>();   
    Logger::Warning("Game Constructor Called");
}

void Game::Run()
{
    Preload();
    BeginPlay();
    while (isRunning)
    {
        Inputs();
        Update();
        Draw();
    }
}
void Game::Preload()
{
    window.create(sf::VideoMode(screenResolution),"Game");
    luaState.open_libraries(sol::lib::base, sol::lib::math);
    //imgui
    if (!ImGui::SFML::Init(window)) {
        // Handle initialization failure
        return; // Or any other appropriate action
    }
}

void Game::BeginPlay()
{
    registry->AddSystem<SMovement>();
    registry->AddSystem<SRender>();
    registry->AddSystem<SAnimation>();
    registry->AddSystem<SCollision>();
    registry->AddSystem<SDebugRender>();
    registry->AddSystem<SDamage>();
    registry->AddSystem<SInput>();
    registry->AddSystem<SCamera>();
    registry->AddSystem<SProjectileEmitter>();
    registry->AddSystem<SRenderDebugGUI>();

    window.setFramerateLimit(frameRate);
        
    cameraActor.setPosition(sf::Vector2f{0,0});
    cameraActor.setScale(static_cast<sf::Vector2f>(window.getSize()));
    isRunning =true;

    auto levelLoader = std::make_unique<LevelLoader>();
    levelLoader->SetupAndLoad(registry.get(),assetStore.get(),luaState,1);
    
    // Fix time step
    timeSinceLastTick = sf::Time::Zero;
    DeltaTime = sf::seconds(1.f / FPS);
}

void Game::PostLoad() {}

void Game::Update()
{
    sf::Time elapsedTime = gameClock.restart();
    timeSinceLastTick += elapsedTime;
    const sf::Time MaxAccumulateTime = sf::seconds(0.25f);
    if(timeSinceLastTick > MaxAccumulateTime)
    {
        timeSinceLastTick = MaxAccumulateTime;
    }
    float DeltaTimeSecond = DeltaTime.asSeconds();
    // fixed update loop
    while (timeSinceLastTick >= DeltaTime)
    {
        //housecleaning subscribers
        eventBus->Reset();
        // the subscribing would be frame by frame
        // TODO : this should be handle out of update
        registry->GetSystem<SDamage>().SubscribeToEvents(eventBus);
        registry->GetSystem<SInput>().SubscribeToEvents(eventBus);
        registry->GetSystem<SProjectileEmitter>().SubscribeToEvent(eventBus);

        //run this at the end of the frame.
        registry->Update();
        registry->GetSystem<SMovement>().Update(DeltaTimeSecond);
        registry->GetSystem<SCamera>().Update(cameraActor,DeltaTime);
        registry->GetSystem<SAnimation>().Update();
        registry->GetSystem<SCollision>().Update(DeltaTimeSecond, eventBus);
        registry->GetSystem<SProjectileEmitter>().Update(DeltaTimeSecond,registry);
        timeSinceLastTick -= DeltaTime;
    }  
    CurrentGameFPS = 1.f / elapsedTime.asSeconds();
}
void Game::Draw()
{
    window.clear(sf::Color(18,33,43));
    registry->GetSystem<SRender>().Update(window, assetStore.get(), cameraActor);
    
    if(bDebug)
    {
        registry->GetSystem<SDebugRender>().
                Update(window,cameraActor,registry->GetSystem<SCollision>().GetHitColor());
        registry->GetSystem<SRenderDebugGUI>().Update(window,DeltaTime,registry,cameraActor);
    }
    window.display();
}

void Game::EndPlay()
{
    isRunning = false;
    ImGui::SFML::Shutdown();
    window.close();
}

void Game::Inputs()
{
    // Check if the game was closed.
    static bool bPKeyPressed;
    while(const std::optional event = window.pollEvent())
    {
        ImGui::SFML::ProcessEvent(window,*event);
        if (event->is<sf::Event::Closed>())
        {
            EndPlay();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
        {
            window.create(sf::VideoMode::getDesktopMode(), "", sf::State::Fullscreen);
            window.setFramerateLimit(60);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            frameRate+=10;
            window.setFramerateLimit(frameRate);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {

            (frameRate>10)?frameRate-=5 : frameRate=5;
            window.setFramerateLimit(frameRate);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)&& !bPKeyPressed)
        {
            bDebug = !bDebug;
            bPKeyPressed=true;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
        {
            bPKeyPressed = false;
        }
        if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            eventBus->EmitEvent<KeyPressedEvent>(keyPressed->code);
        }
    }
}

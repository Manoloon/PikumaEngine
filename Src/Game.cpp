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
#include "Systems/SRenderText.h"
#include "Systems/SScript.h"
#include "Systems/SProjectile.h"
#include "LevelLoader.h"

float Game::mapWidth;
float Game::mapHeight;
sf::Vector2u Game::viewSize;

Game::Game()
{
    registry = std::make_unique<Registry>();
    assetStore = std::make_unique<AssetStore>();
    eventBus = std::make_unique<EventBus>();   
    Logger::Info("Game Constructor Called");
}

void Game::Run()
{
    Preload();
    BeginPlay();
    PostLoad();
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
    luaState.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);
    registry->AddSystem<SMovement>();
    registry->AddSystem<SRender>();
    registry->AddSystem<SAnimation>();
    registry->AddSystem<SCollision>();
    registry->AddSystem<SDebugRender>();
    registry->AddSystem<SProjectile>();
    registry->AddSystem<SDamage>();
    registry->AddSystem<SInput>();
    registry->AddSystem<SCamera>();
    registry->AddSystem<SProjectileEmitter>();
    registry->AddSystem<SRenderDebugGUI>();
    registry->AddSystem<SRenderText>();
    registry->AddSystem<SScript>();
    registry->GetSystem<SScript>().CreateBindings(luaState);
    
    window.setFramerateLimit(frameRate);
    auto levelLoader = std::make_unique<LevelLoader>();
    levelLoader->SetupAndLoad(registry.get(),assetStore.get(),luaState,1);
    registry->Update();
    //imgui
    if (!ImGui::SFML::Init(window)) {
        // Handle initialization failure
        return; // Or any other appropriate action
    }
    Logger::Info("Game::Preload Finished");
}

void Game::BeginPlay()
{
    isRunning =true;
    auto& cameraSystem = registry->GetSystem<SCamera>();
    cameraSystem.BeginPlay(registry.get());
    auto player = registry->GetEntityByTag("player");
    if(!player.HasComponent<CCamera>())
    {
        Logger::Error("Game::BeginPlay : Failed to get the CCamera from the player");
        return;
    }
    CameraActor = &player.GetComponent<CCamera>();
    // Fix time step
    timeSinceLastTick = sf::Time::Zero;
    DeltaTime = sf::seconds(1.f / FPS);
    Logger::Info("Game::BeginPlay Finished");
}

void Game::PostLoad() 
{
    Logger::Info("Game::Postload Finished");
}

void Game::Update()
{
    sf::Time frameTime = gameClock.restart();
    totalElapsedTime += frameTime; 
    timeSinceLastTick += frameTime;
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
        registry->GetSystem<SDamage>().SubscribeToEvents(*eventBus);
        registry->GetSystem<SProjectileEmitter>().SubscribeToEvent(*eventBus);
        //run this at the end of the frame.
        registry->Update();
        registry->GetSystem<SInput>().Update();
        registry->GetSystem<SMovement>().Update(DeltaTimeSecond);
        registry->GetSystem<SAnimation>().Update();
        registry->GetSystem<SCamera>().Update();
        registry->GetSystem<SProjectile>().Update(DeltaTimeSecond);
        registry->GetSystem<SCollision>().Update(*eventBus);
        registry->GetSystem<SProjectileEmitter>().Update(DeltaTimeSecond,*registry);
        registry->GetSystem<SScript>().Update(DeltaTimeSecond,totalElapsedTime.asSeconds());

        timeSinceLastTick -= DeltaTime;
    }
    CurrentGameFPS = 1.f / frameTime.asSeconds();
}
void Game::Draw()
{
    window.clear(sf::Color(18,33,43));
    
    // World render
    registry->GetSystem<SRender>().Update(window, assetStore.get(), *CameraActor);

    if(bDebug)
    {
        registry->GetSystem<SDebugRender>().Update(window,*CameraActor,registry->GetSystem<SCollision>().GetHitColor());
    }

    // UI / screen space render
    //window.setView(window.getDefaultView());
    registry->GetSystem<SRenderText>().Draw(window,assetStore.get(),*CameraActor);
    if(bDebug)
    {
        registry->GetSystem<SRenderDebugGUI>().Update(window,DeltaTime,registry,*CameraActor);
    }
    window.display();
}

void Game::EndPlay()
{
    isRunning = false;
    ImGui::SFML::Shutdown();
    window.close();
    Logger::Info("Game::EndPlay Finished");
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

            if(frameRate>10)
            {
                frameRate-=5;
            }
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

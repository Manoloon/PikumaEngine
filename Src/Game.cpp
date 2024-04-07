//
// Created by Manoloon on 13/05/2022.
//
#include <fstream>

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
    // window
    window.create(sf::VideoMode(screenResolution.x,screenResolution.y),"");
    
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

    assetStore->AddTexture("tank-image","../assets/images/tank-panther-right.png");
    assetStore->AddTexture("truck-image","../assets/images/truck-ford-right.png");
    assetStore->AddTexture("player-image","../assets/images/chopper-spritesheet.png");
    assetStore->AddTexture("radar-image","../assets/images/radar.png");
    assetStore->AddTexture("tilemap-image","../assets/tilemaps/jungle.png");
    assetStore->AddTexture("bullet-image","../assets/images/bullet.png");
    assetStore->AddTexture("tree-image","../assets/images/tree.png");
    
    window.setFramerateLimit(frameRate);
        
    cameraActor.setPosition(0,0);
    cameraActor.setScale(window.getSize().x,window.getSize().y);
    isRunning =true;

    LoadLevel(1);
    
    // Fix time step
    timeSinceLastTick = sf::Time::Zero;
    DeltaTime = sf::seconds(1.f / FPS);
}

// TODO ::: PROBLEM IS HERE
void Game::LoadLevel(int newLevel) const
{
    // load tilemap
    // load the tilemap map from ./assets/tilemaps/jungle.map
    // could I use rect as the switcher for every tile
    // consider creating an entity per tile

    //read the file map.
    std::fstream mapFile;
    mapFile.open("../assets/tilemaps/jungle.map");
    if(mapFile.fail())
    {
        Logger::Error("Failed to read the tilemap.map file");
        exit(1);
    }
    else
    {
        for(int y=0;y<MAP_ROWS;y++)
        {
            for(int x=0;x<MAP_COLUMNS;x++)
            {
                char ch[2]={0,0};
                mapFile.get(ch[0]);
                int srcRectY=std::atoi(&ch[0]) * (int)TILE_SIZE;
                mapFile.get(ch[0]);
                int srcRectX=std::atoi(&ch[0]) * (int)TILE_SIZE;
                mapFile.ignore();

                Entity tile = registry->CreateEntity();
                tile.Group("tiles");
                tile.AddComponent<CTransform>(sf::Vector2f(x * (TILE_SCALE * TILE_SIZE),
                                                              y * (TILE_SCALE * TILE_SIZE)),
                                              sf::Vector2f(TILE_SCALE,TILE_SCALE),
                                              0.0f);
                tile.AddComponent<CSprite>("tilemap-image",
                                           sf::Vector2f(TILE_SIZE,TILE_SIZE),
                                           ERenderLayers::LAYER_TILEMAP, false,
                                           sf::Vector2f(srcRectX,srcRectY));
            }
        }
        mapFile.close();
        mapWidth = MAP_COLUMNS * TILE_SIZE * TILE_SCALE;
        mapHeight = MAP_ROWS * TILE_SIZE * TILE_SCALE;
    }

    Entity Tank = registry->CreateEntity();
    Tank.Group("Enemies");
    Tank.AddComponent<CTransform>(sf::Vector2f(10, 50), sf::Vector2f(2.0, 2.0), 0.0);
    Tank.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    Tank.AddComponent<CShootEmitter>(sf::Vector2f(50,10),2000,2000,false);
    Tank.AddComponent<CSprite>("tank-image", sf::Vector2f(32.f, 32.f), ERenderLayers::LAYER_ENEMIES);
    Tank.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity Truck = registry->CreateEntity();
    Truck.Group("Enemies");
    Truck.AddComponent<CTransform>(sf::Vector2f(200, 50), sf::Vector2f(1.0, 1.0), 0.0);
    Truck.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    Truck.AddComponent<CShootEmitter>(sf::Vector2f(40,0),5000,1000,false);
    Truck.AddComponent<CSprite>("truck-image", sf::Vector2f(32.f, 32.f), ERenderLayers::LAYER_ENEMIES);
    Truck.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity Player = registry->CreateEntity();
    Player.Tag("Player");
    Player.AddComponent<CTransform>(sf::Vector2f(50, 50), sf::Vector2f(4.0, 4.0), 0.0);
    Player.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    Player.AddComponent<CSprite>("player-image", sf::Vector2f(32.f, 32.f), ERenderLayers::LAYER_PLAYER);
    Player.AddComponent<CAnimation>(2, 6);
    Player.AddComponent<CHealth>(100);
    Player.AddComponent<CCameraFollow>();
    Player.AddComponent<CShootEmitter>(sf::Vector2f(150,150),0,1000,true,0);
    Player.AddComponent<CKeyboardControlled>(sf::Vector2f(0, -PLAYER_VELOCITY),
                                             sf::Vector2f(PLAYER_VELOCITY,0),
                                             sf::Vector2f(0,PLAYER_VELOCITY),
                                             sf::Vector2f(-PLAYER_VELOCITY,0));
    //Player.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity chop2 = registry->CreateEntity();
    chop2.Group("Enemies");
    chop2.AddComponent<CTransform>(sf::Vector2f(150, 150), sf::Vector2f(2.0, 2.0), 0.0);
    chop2.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    chop2.AddComponent<CSprite>("player-image", sf::Vector2f(32.f, 32.f), ERenderLayers::LAYER_PLAYER);
    chop2.AddComponent<CAnimation>(2, 12);
    //chop2.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity chop1 = registry->CreateEntity();
    chop1.Group("Enemies");
    chop1.AddComponent<CTransform>(sf::Vector2f(250, 250), sf::Vector2f(1.0, 1.0), 0.0);
    chop1.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    chop1.AddComponent<CSprite>("player-image", sf::Vector2f(32.f, 32.f), ERenderLayers::LAYER_PLAYER);
    chop1.AddComponent<CAnimation>(2, 2);
    //chop1.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity tree = registry->CreateEntity();
    tree.Group("Obstacles");
    tree.AddComponent<CTransform>(sf::Vector2f(100.f,500.f));
    tree.AddComponent<CSprite>("tree-image",sf::Vector2f(16.f,32.f),ERenderLayers::LAYER_OBSTACLES);
    tree.AddComponent<CBoxCollision>(sf::Vector2f(16.f, 32.f));

    Entity UI_Radar = registry->CreateEntity();
    UI_Radar.AddComponent<CTransform>(sf::Vector2f(screenResolution.x - 100, 50));
    UI_Radar.AddComponent<CSprite>("radar-image", sf::Vector2f(64.f, 64.f),
                                   ERenderLayers::LAYER_GUI, true);
    UI_Radar.AddComponent<CAnimation>(8, 5);
}

void Game::Update()
{
    sf::Time elapsedTime = gameClock.restart();
    timeSinceLastTick += elapsedTime;
    while (timeSinceLastTick >= DeltaTime)
    {
        //housecleaning subscribers
        eventBus->Reset();
        // the subscribing would be frame by frame
        registry->GetSystem<SDamage>().SubscribeToEvents(eventBus);
        registry->GetSystem<SInput>().SubscribeToEvents(eventBus);
        registry->GetSystem<SProjectileEmitter>().SubscribeToEvent(eventBus);

        //run this at the end of the frame.
        registry->Update();
        registry->GetSystem<SMovement>().Update(timeSinceLastTick.asSeconds());
        registry->GetSystem<SCamera>().Update(cameraActor,DeltaTime);
        registry->GetSystem<SAnimation>().Update();
        registry->GetSystem<SCollision>().Update(timeSinceLastTick.asSeconds(), eventBus);
        registry->GetSystem<SProjectileEmitter>().Update(timeSinceLastTick.asMilliseconds(),registry);
        timeSinceLastTick -= DeltaTime;
    }  
    CurrentFPS = 1.f / elapsedTime.asSeconds();
}
void Game::Draw()
{
    window.clear(sf::Color(18,33,43));
    registry->GetSystem<SRender>().Update(window, assetStore, cameraActor);
    
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
    sf::Event event;
    static bool bPKeyPressed;
    if (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        
        if ((event.type == sf::Event::Closed) ||
            (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
        {
            EndPlay();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            window.create(sf::VideoMode::getDesktopMode(), "", sf::Style::Fullscreen);
            window.setFramerateLimit(60);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            frameRate+=10;
            window.setFramerateLimit(frameRate);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {

            (frameRate>10)?frameRate-=5 : frameRate=5;
            window.setFramerateLimit(frameRate);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)&& !bPKeyPressed)
        {
            bDebug = !bDebug;
            bPKeyPressed=true;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            bPKeyPressed = false;
        }
        eventBus->EmitEvent<KeyPressedEvent>(event.key.code);
    }
}

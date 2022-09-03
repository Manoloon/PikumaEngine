//
// Created by Manoloon on 13/05/2022.
//
#include <fstream>
#include "Game.h"
#include "ECS/ECS.h"
#include "ECS/AssetStore.h"
#include "Systems/SMovement.h"
#include "Systems/SRender.h"
#include "Systems/SAnimation.h"
#include "Systems/SCollision.h"
#include "Systems/SInput.h"
#include "Systems/SDebugRender.h"
#include "Systems/SDamage.h"
#include "Systems/SCamera.h"

float Game::mapWidth;
float Game::mapHeight;

Game::Game()
{
     registry = std::make_unique<Registry>();
     assetStore = std::make_unique<AssetStore>();
     eventBus = std::make_unique<EventBus>();
}

void Game::Run()
{
    BeginPlay();
    while (isRunning)
    {
        Inputs();
        Update();
        Draw();
    }
}

void Game::LoadLevel(int) const
{
    registry->AddSystem<SMovement>();
    registry->AddSystem<SRender>();
    registry->AddSystem<SAnimation>();
    registry->AddSystem<SCollision>();
    registry->AddSystem<SDebugRender>();
    registry->AddSystem<SDamage>();
    registry->AddSystem<SInput>();
    registry->AddSystem<SCamera>();

    assetStore->AddTexture("tank-image","./assets/images/tank-panther-right.png");
    assetStore->AddTexture("truck-image","./assets/images/truck-ford-right.png");
    assetStore->AddTexture("player-image","./assets/images/chopper-spritesheet.png");
    assetStore->AddTexture("radar-image","../assets/images/radar.png");
    assetStore->AddTexture("tilemap-image","./assets/tilemaps/jungle.png");
    // load tilemap
    // load the tilemap map from ./assets/tilemaps/jungle.map
    // could I use rect as the switcher for every tile
    // consider creating an entity per tile
    float tileSize = 32.f;
    float tileScale = 1.0;
    int mapNumCols = 25;
    int mapNumRows = 20;
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
        for(int y=0;y<mapNumRows;y++)
        {
            for(int x=0;x<mapNumCols;x++)
            {
                char ch[2]={0,0};
                mapFile.get(ch[0]);
                int srcRectY=std::atoi(&ch[0]) * (int)tileSize;
                mapFile.get(ch[0]);
                int srcRectX=std::atoi(&ch[0]) * (int)tileSize;
                mapFile.ignore();

                Entity tile = registry->CreateEntity();
                tile.AddComponent<CTransform>(sf::Vector2f(x * (tileScale * tileSize),
                                                              y * (tileScale * tileSize)),
                                              sf::Vector2f(tileScale,tileScale),
                                              0.0f);
                tile.AddComponent<CSprite>("tilemap-image",
                                           sf::Vector2f(tileSize,tileSize),
                                           ERenderLayers::LAYER_TILEMAP, false,
                                           sf::Vector2f(srcRectX,srcRectY));
            }
        }
        mapFile.close();
        mapWidth = mapNumCols * tileSize * tileScale;
        mapHeight = mapNumRows * tileSize * tileScale;
    }

    //////////////////////
    Entity Tank = registry->CreateEntity();
    Tank.AddComponent<CTransform>(sf::Vector2f(10, 50), sf::Vector2f(2.0, 2.0), 0.0);
    Tank.AddComponent<CRigidBody>(sf::Vector2f(30.f, 0.f));
    Tank.AddComponent<CBoxCollision>(sf::Vector2f(64.f, 64.f));
    Tank.AddComponent<CSprite>("tank-image", sf::Vector2f(32.f, 32.f), ERenderLayers::LAYER_ENEMIES);

    Entity Truck = registry->CreateEntity();
    Truck.AddComponent<CTransform>(sf::Vector2f(200, 50), sf::Vector2f(1.0, 1.0), 0.0);
    Truck.AddComponent<CRigidBody>(sf::Vector2f(-30.f, 0.f));
    Truck.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));
    Truck.AddComponent<CSprite>("truck-image", sf::Vector2f(32.f, 32.f), ERenderLayers::LAYER_ENEMIES);

    Entity Player = registry->CreateEntity();
    Player.AddComponent<CTransform>(sf::Vector2f(50, 50), sf::Vector2f(4.0, 4.0), 0.0);
    Player.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    Player.AddComponent<CSprite>("player-image", sf::Vector2f(32.f, 32.f), ERenderLayers::LAYER_PLAYER);
    //Frames , Velocity of frames
    Player.AddComponent<CAnimation>(2, 6);
    Player.AddComponent<CCameraFollow>();
    // UP, RIGHT, DOWN, LEFT
    Player.AddComponent<CKeyboardControlled>(sf::Vector2f(0, -playerVelocity),
                                             sf::Vector2f(playerVelocity,0),
                                             sf::Vector2f(0,playerVelocity),
                                             sf::Vector2f(-playerVelocity,0));

    Entity chop2 = registry->CreateEntity();
    chop2.AddComponent<CTransform>(sf::Vector2f(150, 150), sf::Vector2f(2.0, 2.0), 0.0);
    chop2.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    chop2.AddComponent<CSprite>("player-image", sf::Vector2f(32.f, 32.f), ERenderLayers::LAYER_PLAYER);
    chop2.AddComponent<CAnimation>(2, 12);

    Entity chop1 = registry->CreateEntity();
    chop1.AddComponent<CTransform>(sf::Vector2f(250, 250), sf::Vector2f(1.0, 1.0), 0.0);
    chop1.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    chop1.AddComponent<CSprite>("player-image", sf::Vector2f(32.f, 32.f), ERenderLayers::LAYER_PLAYER);
    chop1.AddComponent<CAnimation>(2, 2);


    Entity UI_Radar = registry->CreateEntity();
    UI_Radar.AddComponent<CTransform>(sf::Vector2f(screenResolution.x - 100, 50));
    UI_Radar.AddComponent<CSprite>("radar-image", sf::Vector2f(64.f, 64.f),
                                   ERenderLayers::LAYER_GUI, true);
    UI_Radar.AddComponent<CAnimation>(8, 5);
}

void Game::BeginPlay()
{
    // window
    window.create(sf::VideoMode(screenResolution.x,screenResolution.y),"");
    // Fix time step
    timeSinceLastTick = sf::Time::Zero;
    DeltaTime = sf::seconds(1.f / FPS);
    isRunning =true;
    LoadLevel(1);
    cameraActor.setPosition(0,0);
    cameraActor.setScale(window.getSize().x,window.getSize().y);
}

void Game::Update()
{
   timeSinceLastTick +=gameClock.restart();
    while (timeSinceLastTick > DeltaTime)
    {
        //housecleaning subscribers
        eventBus->Reset();
        // the subscribing would be frame by frame
        registry->GetSystem<SDamage>().SubscribeToEvents(eventBus);
        registry->GetSystem<SInput>().SubscribeToEvents(eventBus);

        //run this at the end of the frame.
        registry->Update();
        registry->GetSystem<SMovement>().Update(timeSinceLastTick.asSeconds());
        registry->GetSystem<SCamera>().Update(timeSinceLastTick.asSeconds(), cameraActor);
        registry->GetSystem<SAnimation>().Update();
        registry->GetSystem<SCollision>().Update(timeSinceLastTick.asSeconds(), eventBus);
        timeSinceLastTick -= DeltaTime;
    }
}
void Game::Draw()
{
    window.clear(sf::Color(18,33,43));
    registry->GetSystem<SRender>().Update(window, assetStore, cameraActor);
    if(bDebug)
    {
        registry->GetSystem<SDebugRender>().
                Update(window,cameraActor,registry->GetSystem<SCollision>().GetHitColor());
    }
    window.display();
}

void Game::EndPlay()
{
    isRunning = false;
    window.close();
}

void Game::Inputs()
{
    // Check if the game was closed.
    sf::Event event;
    if (window.pollEvent(event))
    {
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
       // eventBus->EmitEvent<KeyPressedEvent>(sf::Keyboard::isKeyPressed(sf::key))
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            eventBus->EmitEvent<KeyPressedEvent>(sf::Keyboard::W);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            eventBus->EmitEvent<KeyPressedEvent>(sf::Keyboard::S);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            eventBus->EmitEvent<KeyPressedEvent>(sf::Keyboard::D);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            eventBus->EmitEvent<KeyPressedEvent>(sf::Keyboard::A);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            bDebug = true;
        }
        else
        {
            bDebug= false;
        }
    }
}

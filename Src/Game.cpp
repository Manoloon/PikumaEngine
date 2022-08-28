//
// Created by Manoloon on 13/05/2022.
//
#include <fstream>
#include "Game.h"
#include "ECS/ECS.h"
#include "ECS/AssetStore.h"
#include "Systems/MovementSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/AnimationSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/DebugRenderSystem.h"
#include "Systems/DamageSystem.h"
#include "Systems/CameraSystem.h"

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
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderSystem>();
    registry->AddSystem<AnimationSystem>();
    registry->AddSystem<CollisionSystem>();
    registry->AddSystem<DebugRenderSystem>();
    registry->AddSystem<DamageSystem>();
    registry->AddSystem<InputSystem>();
    registry->AddSystem<CameraSystem>();

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
                tile.AddComponent<TransformComp>(sf::Vector2f(x * (tileScale * tileSize),
                                                              y * (tileScale * tileSize)),
                                                 sf::Vector2f(tileScale,tileScale),
                                                 0.0f);
                tile.AddComponent<SpriteComp>("tilemap-image",
                                              sf::Vector2f(tileSize,tileSize),
                                              ERenderLayers::LAYER_TILEMAP,false,
                                              sf::Vector2f(srcRectX,srcRectY));
            }
        }
        mapFile.close();
        mapWidth = mapNumCols * tileSize * tileScale;
        mapHeight = mapNumRows * tileSize * tileScale;
    }

    //////////////////////
    Entity Tank = registry->CreateEntity();
    Tank.AddComponent<TransformComp>(sf::Vector2f(10,50),sf::Vector2f(2.0,2.0),0.0);
    Tank.AddComponent<RigidBodyComp>(sf::Vector2f(30.f,0.f));
    Tank.AddComponent<BoxCollisionComp>(sf::Vector2f(64.f,64.f));
    Tank.AddComponent<SpriteComp>("tank-image",sf::Vector2f(32.f,32.f),ERenderLayers::LAYER_ENEMIES);

    Entity Truck = registry->CreateEntity();
    Truck.AddComponent<TransformComp>(sf::Vector2f(200,50),sf::Vector2f(1.0,1.0),0.0);
    Truck.AddComponent<RigidBodyComp>(sf::Vector2f(-30.f,0.f));
    Truck.AddComponent<BoxCollisionComp>(sf::Vector2f(32.f,32.f));
    Truck.AddComponent<SpriteComp>("truck-image",sf::Vector2f(32.f,32.f),ERenderLayers::LAYER_ENEMIES);

    Entity Player = registry->CreateEntity();
    Player.AddComponent<TransformComp>(sf::Vector2f(50,50),sf::Vector2f(2.0,2.0),0.0);
    Player.AddComponent<RigidBodyComp>(sf::Vector2f(0.f,0.f));
    Player.AddComponent<SpriteComp>("player-image",sf::Vector2f(32.f,32.f),ERenderLayers::LAYER_PLAYER);
    Player.AddComponent<AnimationComp>(2, 6);
    Player.AddComponent<CameraFollowComp>();
    Player.AddComponent<KeyboardControlledComp>(sf::Vector2f(0,-20),
                                                sf::Vector2f(20,0),
                                                sf::Vector2f(0,20),
                                                sf::Vector2f(-20,0));


    Entity chop2 = registry->CreateEntity();
    chop2.AddComponent<TransformComp>(sf::Vector2f(150,150),sf::Vector2f(2.0,2.0),0.0);
    chop2.AddComponent<RigidBodyComp>(sf::Vector2f(0.f,0.f));
    chop2.AddComponent<SpriteComp>("player-image",sf::Vector2f(32.f,32.f),ERenderLayers::LAYER_PLAYER);
    chop2.AddComponent<AnimationComp>(2, 12);

    Entity chop1 = registry->CreateEntity();
    chop1.AddComponent<TransformComp>(sf::Vector2f(250,250),sf::Vector2f(1.0,1.0),0.0);
    chop1.AddComponent<RigidBodyComp>(sf::Vector2f(0.f,0.f));
    chop1.AddComponent<SpriteComp>("player-image",sf::Vector2f(32.f,32.f),ERenderLayers::LAYER_PLAYER);
    chop1.AddComponent<AnimationComp>(2, 2);


    Entity UI_Radar = registry->CreateEntity();
    UI_Radar.AddComponent<TransformComp>(sf::Vector2f(screenResolution.x-100,50));
    UI_Radar.AddComponent<SpriteComp>("radar-image",sf::Vector2f(64.f,64.f),
                                      ERenderLayers::LAYER_GUI,true);
    UI_Radar.AddComponent<AnimationComp>(8,5);
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
        registry->GetSystem<MovementSystem>().Update(timeSinceLastTick.asSeconds());
        window.clear(sf::Color(18,33,43));

        if(bDebug)
        {
            registry->GetSystem<DebugRenderSystem>().
                    Update(window,cameraActor,registry->GetSystem<CollisionSystem>().GetHitColor());
        }
        //housecleaning subscribers
        eventBus->Reset();
        // the subscribing would be frame by frame
        registry->GetSystem<DamageSystem>().SubscribeToEvents(eventBus);
        registry->GetSystem<InputSystem>().SubscribeToEvents(eventBus);
        //run this at the end of the frame.
        registry->Update();
        registry->GetSystem<RenderSystem>().Update(timeSinceLastTick.asSeconds(),
                                                   window,assetStore,cameraActor);
        registry->GetSystem<AnimationSystem>().Update();
        registry->GetSystem<CollisionSystem>().Update(timeSinceLastTick.asSeconds(),eventBus);
        registry->GetSystem<CameraSystem>().Update(timeSinceLastTick.asSeconds(),cameraActor);
        window.display();
        timeSinceLastTick -= DeltaTime;
    }
}
void Game::Draw()
{
    //window.clear(sf::Color(18,33,43));
    //if(bDebug)
    //{
      //  registry->GetSystem<DebugRenderSystem>().Draw(window);
    //}
    // get all sprites to be rendered in this frame.
    //window.display();
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            /* Noncompliant - the following nested block is empty */
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            eventBus->EmitEvent<KeyPressedEvent>(sf::Keyboard::S);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            /* Noncompliant - the following nested block is empty */
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            /* Noncompliant - the following nested block is empty */
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            bDebug = true;
        }
        else
        {
            bDebug= false;
        }
    }
}

//
// Created by Manoloon on 13/05/2022.
//
#include <fstream>
#include "Game.h"
#include "ECS/ECS.h"
#include "ECS/AssetStore.h"
#include "Systems/MovementSystem.h"
#include "Systems/RenderSystem.h"

Game::Game()
{
     registry = std::make_unique<Registry>();
     assetStore = std::make_unique<AssetStore>();
}

void Game::Run()
{
    BeginPlay();
    while (isRunning)
    {
        Inputs();
        Update();
        //Draw();
    }
}

void Game::LoadLevel(int)
{
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderSystem>();
    assetStore->AddTexture("tank-image","./assets/images/tank-panther-right.png");
    assetStore->AddTexture("truck-image","./assets/images/truck-ford-right.png");
    assetStore->AddTexture("tilemap-image","./assets/tilemaps/jungle.png");
    // load tilemap
    // load the tilemap map from ./assets/tilemaps/jungle.map
    // could I use rect as the switcher for every tile
    // consider creating an entity per tile
    int tileSize = 32;
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
                int srcRectY=std::atoi(&ch[0]) * tileSize;
                Logger::Warning("Y :" + std::to_string(srcRectY));
                mapFile.get(ch[0]);
                int srcRectX=std::atoi(&ch[0]) * tileSize;
                Logger::Warning("X :" + std::to_string(srcRectX));
                mapFile.ignore();

                Entity tile = registry->CreateEntity();
                tile.AddComponent<TransformComp>(sf::Vector2f(x * (tileScale * tileSize),
                                                              y * (tileScale * tileSize)),
                                                 sf::Vector2f(tileScale,tileScale),
                                                 0.0f);
                tile.AddComponent<SpriteComp>("tilemap-image",
                                              sf::Vector2f(tileSize,tileSize),
                                              sf::Vector2f(srcRectX,srcRectY));
            }
        }
        mapFile.close();
    }

    //////////////////////
    //define player
    Entity Tank = registry->CreateEntity();
    Tank.AddComponent<TransformComp>(sf::Vector2f(100,100),sf::Vector2f(2.0,2.0),45.0);
    Tank.AddComponent<RigidBodyComp>(sf::Vector2f(10.f,50.f));
    Tank.AddComponent<SpriteComp>("tank-image",sf::Vector2f(32.f,32.f));
    Entity Truck = registry->CreateEntity();
    Truck.AddComponent<TransformComp>(sf::Vector2f(10,50),sf::Vector2f(1.0,1.0),10.0);
    Truck.AddComponent<RigidBodyComp>(sf::Vector2f(50.f,10.f));
    Truck.AddComponent<SpriteComp>("truck-image",sf::Vector2f(32.f,32.f));
}

void Game::BeginPlay()
{
    // window
    window.create(sf::VideoMode(800,600),"");
    const float FPS = 60.0f;
    //window.setFramerateLimit(FPS);
    // Fix time step
    timeSinceLastTick = sf::Time::Zero;
    DeltaTime = sf::seconds(1.f / FPS);
    tickDuration= sf::Time::Zero;
    isRunning =true;
    LoadLevel(1);
}

void Game::Update()
{
    timeSinceLastTick +=clock.restart();
    while (timeSinceLastTick > DeltaTime)
    {
        timeSinceLastTick -= DeltaTime;
        registry->GetSystem<MovementSystem>().Update(DeltaTime.asSeconds());
        window.clear(sf::Color(18,33,43));
        registry->GetSystem<RenderSystem>().Update(DeltaTime.asSeconds(), window,assetStore);
        window.display();
        // collisionSystem.Update(DeltaTime);
        //run this at the end of the frame.
        registry->Update();
    }
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

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {

        }
    }
}

void Game::Draw()
{
    window.clear(sf::Color(18,33,43));
    // get all sprites to be rendered in this frame.
    window.display();
}

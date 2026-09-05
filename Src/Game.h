//
// Created by Manoloon on 13/05/2022.
//
#pragma once 

#include <SFML/Graphics.hpp>
#include <vector>
#include "ECS/AssetStore.h"
#include "ECS/ECS.h"
#include "ECS/EventBus.h"
#include <sol/sol.hpp>

class Game
{
    const float FPS = 60.0f;

    sf::RenderWindow window;
    //Fix time step
    sf::Clock gameClock;
    sf::Time DeltaTime;
    sf::Time timeSinceLastTick;
    sf::Time totalElapsedTime = sf::Time::Zero;

    int frameRate = 60;
    std::unique_ptr<Registry> registry;
    std::unique_ptr<AssetStore> assetStore;
    std::unique_ptr<EventBus> eventBus;
    sol::state luaState;

    bool isRunning =false;
    // TODO : Dato que viene desde script
    bool bDebug= false;
    
    sf::Vector2u screenResolution ={800,450};
public:   
    Game();
    void Run();
    void Preload();
    void PostLoad();
    void BeginPlay();
    void EndPlay();
    void Update();
    void Inputs();
    void Draw();
    const CCamera* CameraActor;
    static float mapWidth;
    static float mapHeight;
    static sf::Vector2u viewSize;
};

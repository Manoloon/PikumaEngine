//
// Created by Manoloon on 13/05/2022.
//
#pragma once 

#include <SFML/Graphics.hpp>
#include <vector>
#include "ECS/AssetStore.h"
#include "ECS/ECS.h"
#include "ECS/EventBus.h"

class Game
{
    const float FPS = 60.0f;

    sf::RenderWindow window;
    //Fix time step
    sf::Clock gameClock;
    sf::Time DeltaTime;
    sf::Time timeSinceLastTick;
    sf::Vector2i screenResolution={800,600};
    int frameRate = 60;
    std::unique_ptr<Registry> registry;
    std::unique_ptr<AssetStore> assetStore;
    std::unique_ptr<EventBus> eventBus;
    bool isRunning =false;
    bool bDebug= false;
    sf::RectangleShape cameraActor;

public:
    Game();
    void Run();
    void LoadLevel(int newLevel) const;
    void BeginPlay();
    void EndPlay();
    void Update();
    void Inputs();
    void Draw();

    static float mapWidth;
    static float mapHeight;
};

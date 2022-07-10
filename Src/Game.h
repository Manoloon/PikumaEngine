//
// Created by Manoloon on 13/05/2022.
//

#ifndef PIKUMAENGINE_GAME_H
#define PIKUMAENGINE_GAME_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "ECS/AssetStore.h"
#include "ECS/ECS.h"

class Game
{
    const float FPS = 60.0f;
    const int MILLISECS_PER_FRAME = 1000 / FPS;

    sf::RenderWindow window;
    //Fix time step
    sf::Clock clock;
    sf::Time DeltaTime;
    sf::Time timeSinceLastTick;

    int frameRate=60;
    std::unique_ptr<Registry> registry;
    std::unique_ptr<AssetStore> assetStore;
    bool isRunning =false;

public:
    Game();
    void Run();
    void LoadLevel(int newLevel);
    void BeginPlay();
    void EndPlay();
    void Update();
    void Inputs();
    void Draw();
};


#endif //PIKUMAENGINE_GAME_H

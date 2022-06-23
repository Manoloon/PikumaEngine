//
// Created by Manoloon on 13/05/2022.
//

#ifndef PIKUMAENGINE_GAME_H
#define PIKUMAENGINE_GAME_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "ECS/ECS.h"

class Game
{
    sf::RenderWindow window;
    //Fix time step
    sf::Clock clock;
    sf::Time DeltaTime;
    sf::Time timeSinceLastTick;
    sf::Time tickDuration;

    int frameRate=60;
    sf::Texture texPlayer;
    sf::Sprite sprPlayer;
    sf::Vector2f Velocity{0,0};
    std::unique_ptr<Registry> registry;
    bool isRunning =false;

public:
    Game();
    void Run();
    void BeginPlay();
    void EndPlay();
    void Update();
    void Inputs();
    void Draw();
};


#endif //PIKUMAENGINE_GAME_H

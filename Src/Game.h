//
// Created by Manoloon on 13/05/2022.
//

#ifndef PIKUMAENGINE_GAME_H
#define PIKUMAENGINE_GAME_H
#include <SFML/Graphics.hpp>
#include <vector>

class Game
{
    sf::RenderWindow window;
    sf::Clock clock;
    float DeltaTime;
    int frameRate=60;
    sf::Texture texPlayer;
    sf::Sprite sprPlayer;
    sf::Vector2f Velocity{0,0};
    bool isRunning =false;
    void BeginPlay();
    void EndPlay();
    void Tick();
    void Inputs();
    void Draw();

public:
    void Run();
};


#endif //PIKUMAENGINE_GAME_H

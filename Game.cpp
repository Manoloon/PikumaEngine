//
// Created by Manoloon on 13/05/2022.
//

#include "Game.h"

void Game::BeginPlay()
{
    window.create(sf::VideoMode(800,600),"");
    isRunning =true;
}

void Game::EndPlay()
{
    window.close();
}

void Game::Tick()
{

}

void Game::Run()
{
    while (isRunning)
    {
        Inputs();
        Tick();
        Draw();
    }
}

void Game::Inputs()
{
    // Check if the game was closed.
    sf::Event event;
    if (window.pollEvent(event))
    {
        if ((event.type == sf::Event::Closed) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
        {
            isRunning = false;
            return;
        }
    }
}

void Game::Draw()
{

}

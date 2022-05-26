//
// Created by Manoloon on 13/05/2022.
//
#include "Game.h"
#include "ECS/ECS.h"
#include "Logger.h"

void Game::BeginPlay()
{
    //define player
    // Registry.AddEntity();
    // window
    window.create(sf::VideoMode(800,600),"");
    window.setFramerateLimit(60);
    isRunning =true;
}

void Game::EndPlay()
{
    isRunning = false;
    window.close();
}

void Game::Run()
{
    BeginPlay();
    while (isRunning)
    {
        Inputs();
        DeltaTime = clock.restart().asSeconds();
        Tick();
        Draw();
        }
}

void Game::Tick()
{
    // movementSystem.Update(DeltaTime);
    // collisionSystem.Update(DeltaTime);
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
            Velocity={0,-100};
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            Velocity={0,100};
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            Velocity={100,0};
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            Velocity={-100,0};
        }
    }
}

void Game::Draw()
{
    window.clear(sf::Color(18,33,43));
    window.draw(sprPlayer);
    window.display();
}

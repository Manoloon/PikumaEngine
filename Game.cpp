//
// Created by Manoloon on 13/05/2022.
//

#include "Game.h"

void Game::BeginPlay()
{
    //define player
    texPlayer.loadFromFile("assets/images/tank-panther-right.png");
    sprPlayer.setTexture(texPlayer);
    sprPlayer.setPosition(200,200);
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

void Game::Tick(float DeltaTime)
{
    sprPlayer.setRotation(sprPlayer.getRotation()+1);
    sprPlayer.setPosition(sprPlayer.getPosition().x+1,sprPlayer.getPosition().y+1);
}

void Game::Run()
{
    float currentTime = clock.restart().asSeconds();
    float timeDelta = 0.f;
    BeginPlay();
    while (isRunning)
    {
        Inputs();
        float newTime = clock.getElapsedTime().asSeconds();
        float frameTime = std::max(0.f, newTime - currentTime);
        currentTime = newTime;
        Tick(frameTime);
        Draw();

    }
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
    }
}

void Game::Draw()
{
    window.clear(sf::Color(18,33,43));
    window.draw(sprPlayer);
    window.display();
}

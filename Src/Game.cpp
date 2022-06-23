//
// Created by Manoloon on 13/05/2022.
//
#include "Game.h"
#include "ECS/ECS.h"
#include "Logger.h"
#include "Systems/MovementSystem.h"
#include "Systems/RenderSystem.h"

Game::Game()
{
     registry = std::make_unique<Registry>();
}

void Game::Run()
{
    BeginPlay();
    while (isRunning)
    {
        Inputs();
        Update();
       // Draw();
    }
}

void Game::BeginPlay()
{
    // window
    window.create(sf::VideoMode(800,600),"");
    float fps = 60.0f;
    window.setFramerateLimit(fps);
    // Fix time step
    timeSinceLastTick = sf::Time::Zero;
    DeltaTime = sf::seconds(1.f/fps);
    tickDuration= sf::Time::Zero;
    /////////////////////////////////////
    //Add system needed to processed.
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderSystem>();
    //define player
    Entity Tank = registry->CreateEntity();
    Tank.AddComponent<TransformComp>(sf::Vector2f(100,100),sf::Vector2f(2,2),40);
    Tank.AddComponent<RigidBodyComp>(sf::Vector2f(10.f,50.f));
    Tank.AddComponent<SpriteComp>(sf::Vector2f(10,10));
    isRunning =true;
}

void Game::Update()
{
    timeSinceLastTick +=clock.restart();
    while (timeSinceLastTick > DeltaTime)
    {
        timeSinceLastTick -= DeltaTime;
        registry->GetSystem<MovementSystem>().Update(DeltaTime.asSeconds());
        registry->GetSystem<RenderSystem>().Update(DeltaTime.asSeconds(), window);
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
    window.display();
}

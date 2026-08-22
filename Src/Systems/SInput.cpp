#include "SInput.h"
#include <cmath>

SInput::SInput()
{
    RequireComponent<CKeyboardControlled>();
}

void SInput::Update(float deltaTime)
{
    for (auto entity : GetSystemEntities())
    {
        if(!entity.HasComponent<CKeyboardControlled>())
        {
            return;
        }
        auto& keyboard = entity.GetComponent<CKeyboardControlled>();
        keyboard.inputDirection = {0.f,0.f};

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            keyboard.inputDirection += keyboard.up;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            keyboard.inputDirection += keyboard.down;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            keyboard.inputDirection += keyboard.left;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            keyboard.inputDirection += keyboard.right;

        if(keyboard.inputDirection.lengthSquared() > 0.f)
        {
            keyboard.inputDirection = keyboard.inputDirection.normalized();
            keyboard.facingDirection = keyboard.inputDirection;
        }

        // if(inputDir != sf::Vector2f(0.0,0.0))
        // {
        //     inputDir = inputDir.normalized();
        //     keyboard.facingDirection = inputDir;
        //     rigidBody.velocity = inputDir * keyboard.acceleration * deltaTime;
        //     const float speed = rigidBody.velocity.length();
        //     if(speed > keyboard.maxSpeed)
        //     {
        //         rigidBody.velocity = rigidBody.velocity.normalized() * keyboard.maxSpeed;
        //     }

        //     // Update sprite direction based on last pressed axis
        //     if (inputDir.y < 0) sprite.spriteRect.position.y = sprite.spriteRect.size.y * 0; // Up
        //     else if (inputDir.y > 0) sprite.spriteRect.position.y = sprite.spriteRect.size.y * 2; // Down
        //     else if (inputDir.x < 0) sprite.spriteRect.position.y = sprite.spriteRect.size.y * 3; // Left
        //     else if (inputDir.x > 0) sprite.spriteRect.position.y = sprite.spriteRect.size.y * 1; // Right
        // }
        // else
        // {
        //     rigidBody.velocity *= std::pow(keyboard.damping,deltaTime * 60.f);
        //     if(rigidBody.velocity.lengthSquared() < 0.01f)
        //         rigidBody.velocity = {0.0,0.0};
        // }
    }
}
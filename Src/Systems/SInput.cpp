#include "SInput.h"
#include <cmath>

SInput::SInput()
{
    RequireComponent<CKeyboardControlled>();
}

void SInput::Update()
{
    for (auto entity : GetSystemEntities())
    {
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
    }
}
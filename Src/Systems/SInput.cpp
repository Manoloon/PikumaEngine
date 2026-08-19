#include "SInput.h"
#include <cmath>

SInput::SInput()
{
    RequireComponent<CKeyboardControlled>();
    RequireComponent<CSprite>();
    RequireComponent<CRigidBody>();
}

void SInput::SubscribeToEvents(std::unique_ptr<EventBus> &eventBus)
{
    eventBus->SubscribeToEvent<KeyPressedEvent>(this, &SInput::onKeyPressed);
}

void SInput::onKeyPressed(KeyPressedEvent &event)
{
    for (auto entity : GetSystemEntities())
    {
        const auto &keyboardComp = entity.GetComponent<CKeyboardControlled>();
        auto &spriteComp = entity.GetComponent<CSprite>();
        auto &rigidBodyComp = entity.GetComponent<CRigidBody>();

        // multiply the height (32 px) times 0,1,2,3
        if (event.KeySymbol == sf::Keyboard::Key::W)
        {
            rigidBodyComp.velocity += keyboardComp.upVelocity;
            spriteComp.spriteRect.position.y = spriteComp.spriteRect.size.y * 0;
        }

        if (event.KeySymbol == sf::Keyboard::Key::S)
        {
            rigidBodyComp.velocity += keyboardComp.downVelocity;
            spriteComp.spriteRect.position.y = spriteComp.spriteRect.size.y * 2;
        }

        if (event.KeySymbol == sf::Keyboard::Key::A)
        {
            rigidBodyComp.velocity += keyboardComp.leftVelocity;
            spriteComp.spriteRect.position.y = spriteComp.spriteRect.size.y * 3;
        }

        if (event.KeySymbol == sf::Keyboard::Key::D)
        {
            rigidBodyComp.velocity += keyboardComp.rightVelocity;
            spriteComp.spriteRect.position.y = spriteComp.spriteRect.size.y * 1;
        }
    }
}

void SInput::Update(float deltaTime)
{
    /* for (auto entity : GetSystemEntities())
    {
        auto& keyboard = entity.GetComponent<CKeyboardControlled>();
        auto& rigidBody = entity.GetComponent<CRigidBody>();
        auto& sprite = entity.GetComponent<CSprite>();

        sf::Vector2f inputDir = { 0.f, 0.f };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) inputDir += keyboard.up;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) inputDir += keyboard.down;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) inputDir += keyboard.left;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) inputDir += keyboard.right;

        // Normalize input direction if diagonal
        if (inputDir.x != 0.f || inputDir.y != 0.f)
        {
            float length = std::sqrt(inputDir.x * inputDir.x + inputDir.y * inputDir.y);
            inputDir /= length;

            // Apply acceleration
            rigidBody.velocity += inputDir * keyboard.acceleration * deltaTime;

            // Clamp to max speed
            float speed = std::sqrt(rigidBody.velocity.x * rigidBody.velocity.x +
                                    rigidBody.velocity.y * rigidBody.velocity.y);
            if (speed > keyboard.maxSpeed)
            {
                rigidBody.velocity = (rigidBody.velocity / speed) * keyboard.maxSpeed;
            }

            // Update sprite direction based on last pressed axis
            if (inputDir.y < 0) sprite.spriteRect.top = sprite.spriteRect.height * 0; // Up
            else if (inputDir.y > 0) sprite.spriteRect.top = sprite.spriteRect.height * 2; // Down
            else if (inputDir.x < 0) sprite.spriteRect.top = sprite.spriteRect.height * 3; // Left
            else if (inputDir.x > 0) sprite.spriteRect.top = sprite.spriteRect.height * 1; // Right
        }
        else
        {
            // Apply damping (slow down gradually when no keys pressed)
            rigidBody.velocity *= keyboard.damping;
        }
    } */
}
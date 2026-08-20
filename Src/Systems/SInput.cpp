#include "SInput.h"
#include <cmath>

SInput::SInput()
{
    RequireComponent<CKeyboardControlled>();
    RequireComponent<CSprite>();
    RequireComponent<CRigidBody>();
}
[[deprecated]]
void SInput::SubscribeToEvents(std::unique_ptr<EventBus> &eventBus)
{
    eventBus->SubscribeToEvent<KeyPressedEvent>(this, &SInput::onKeyPressed);
}

[[deprecated]]
void SInput::onKeyPressed(KeyPressedEvent &event)
{
//     for (auto entity : GetSystemEntities())
//     {
//         const auto &keyboardComp = entity.GetComponent<CKeyboardControlled>();
//         auto &spriteComp = entity.GetComponent<CSprite>();
//         auto &rigidBodyComp = entity.GetComponent<CRigidBody>();

//         // multiply the height (32 px) times 0,1,2,3
//         if (event.KeySymbol == sf::Keyboard::Key::W)
//         {
//             rigidBodyComp.velocity = keyboardComp.upVelocity;
//             spriteComp.spriteRect.position.y = spriteComp.spriteRect.size.y * 0;
//         }

//         if (event.KeySymbol == sf::Keyboard::Key::S)
//         {
//             rigidBodyComp.velocity = keyboardComp.downVelocity;
//             spriteComp.spriteRect.position.y = spriteComp.spriteRect.size.y * 2;
//         }

//         if (event.KeySymbol == sf::Keyboard::Key::A)
//         {
//             rigidBodyComp.velocity = keyboardComp.leftVelocity;
//             spriteComp.spriteRect.position.y = spriteComp.spriteRect.size.y * 3;
//         }

//         if (event.KeySymbol == sf::Keyboard::Key::D)
//         {
//             rigidBodyComp.velocity = keyboardComp.rightVelocity;
//             spriteComp.spriteRect.position.y = spriteComp.spriteRect.size.y * 1;
//         }
//     }
}

void SInput::Update(float deltaTime)
{
    for (auto entity : GetSystemEntities())
    {
        auto& keyboard = entity.GetComponent<CKeyboardControlled>();
        auto& rigidBody = entity.GetComponent<CRigidBody>();
        auto& sprite = entity.GetComponent<CSprite>();

        sf::Vector2f inputDir = { 0.f, 0.f };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) inputDir += keyboard.up;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) inputDir += keyboard.down;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) inputDir += keyboard.left;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) inputDir += keyboard.right;

        if(inputDir != sf::Vector2f(0.0,0.0))
        {
            inputDir = inputDir.normalized();
            keyboard.facingDirection = inputDir;
            rigidBody.velocity = inputDir * keyboard.acceleration * deltaTime;
            const float speed = rigidBody.velocity.length();
            if(speed > keyboard.maxSpeed)
            {
                rigidBody.velocity = rigidBody.velocity.normalized() * keyboard.maxSpeed;
            }

            // Update sprite direction based on last pressed axis
            if (inputDir.y < 0) sprite.spriteRect.position.y = sprite.spriteRect.size.y * 0; // Up
            else if (inputDir.y > 0) sprite.spriteRect.position.y = sprite.spriteRect.size.y * 2; // Down
            else if (inputDir.x < 0) sprite.spriteRect.position.y = sprite.spriteRect.size.y * 3; // Left
            else if (inputDir.x > 0) sprite.spriteRect.position.y = sprite.spriteRect.size.y * 1; // Right
        }
        else
        {
            rigidBody.velocity *= std::pow(keyboard.damping,deltaTime * 60.f);
            if(rigidBody.velocity.lengthSquared() < 0.01f)
                rigidBody.velocity = {0.0,0.0};
        }
    }
}
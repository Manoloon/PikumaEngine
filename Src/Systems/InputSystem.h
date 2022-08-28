//
// Created by Manoloon on 31/07/2022.
//

#ifndef PIKUMAENGINE_INPUTSYSTEM_H
#define PIKUMAENGINE_INPUTSYSTEM_H

#include "../ECS/ECS.h"
#include "../ECS/EventBus.h"
#include "../Events/KeyPressedEvent.h"

class InputSystem: public System
        {
public:
            InputSystem()
            {
                RequireComponent<KeyboardControlledComp>();
                RequireComponent<SpriteComp>();
                RequireComponent<RigidBodyComp>();
            }
            void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus)
            {
                eventBus->SubscribeToEvent<KeyPressedEvent>(this,&InputSystem::onKeyPressed);
            }
            void onKeyPressed(KeyPressedEvent& event)
            {
                for(auto entity : GetSystemEntities())
                {
                    const auto& keyboardComp = entity.GetComponent<KeyboardControlledComp>();
                    auto& spriteComp = entity.GetComponent<SpriteComp>();
                    auto& rigidBodyComp = entity.GetComponent<RigidBodyComp>();

                    // multiply the height (32 px) times 0,1,2,3
                    switch(event.keySymbol)
                    {
                        case sf::Keyboard::Key::Up:
                            rigidBodyComp.velocity = keyboardComp.upVelocity;
                            spriteComp.spriteRect.top = spriteComp.spriteRect.height *0;
                            break;
                        case sf::Keyboard::Key::Right:
                            rigidBodyComp.velocity = keyboardComp.upVelocity;
                            spriteComp.spriteRect.top = spriteComp.spriteRect.height *1;
                            break;
                        case sf::Keyboard::Key::Down:
                            rigidBodyComp.velocity = keyboardComp.upVelocity;
                            spriteComp.spriteRect.top = spriteComp.spriteRect.height *2;
                            break;
                        case sf::Keyboard::Key::Left:
                            rigidBodyComp.velocity = keyboardComp.upVelocity;
                            spriteComp.spriteRect.top = spriteComp.spriteRect.height *3;
                            break;

                    }
                }
            }
        };
#endif //PIKUMAENGINE_INPUTSYSTEM_H

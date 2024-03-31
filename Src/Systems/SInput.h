//
// Created by Manoloon on 31/07/2022.
//
#pragma once

#include "../ECS/ECS.h"
#include "../ECS/EventBus.h"
#include "../Events/KeyPressedEvent.h"

class SInput: public System
        {
public:
            SInput()
            {
                RequireComponent<CKeyboardControlled>();
                RequireComponent<CSprite>();
                RequireComponent<CRigidBody>();
            }
            void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus)
            {
                eventBus->SubscribeToEvent<KeyPressedEvent>(this,&SInput::onKeyPressed);
            }
            void onKeyPressed(KeyPressedEvent& event)
            {
                for(auto entity : GetSystemEntities())
                {
                    const auto& keyboardComp = entity.GetComponent<CKeyboardControlled>();
                    auto& spriteComp = entity.GetComponent<CSprite>();
                    auto& rigidBodyComp = entity.GetComponent<CRigidBody>();

                    // multiply the height (32 px) times 0,1,2,3
                    if(event.keySymbol == sf::Keyboard::Key::W)
                    {
                        rigidBodyComp.velocity += keyboardComp.upVelocity;
                        spriteComp.spriteRect.top = spriteComp.spriteRect.height *0;
                    }
                    
                    if(event.keySymbol == sf::Keyboard::Key::S)
                    {
                        rigidBodyComp.velocity += keyboardComp.downVelocity;
                        spriteComp.spriteRect.top = spriteComp.spriteRect.height *2;
                    }

                    if(event.keySymbol == sf::Keyboard::Key::A)
                    {
                        rigidBodyComp.velocity += keyboardComp.leftVelocity;
                        spriteComp.spriteRect.top = spriteComp.spriteRect.height *3;
                    }

                    if(event.keySymbol == sf::Keyboard::Key::D)
                    {
                        rigidBodyComp.velocity += keyboardComp.rightVelocity;
                        spriteComp.spriteRect.top = spriteComp.spriteRect.height *1;
                    }
                }
            }
        };

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
            InputSystem()=default;
            void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus)
            {
                eventBus->SubscribeToEvent<KeyPressedEvent>(this,&InputSystem::onKeyPressed);
            }
            void onKeyPressed(KeyPressedEvent& event)
            {
                std::string keyCode = std::to_string(event.keySymbol);
                Logger::Warning("the key pressed was : " + keyCode);
            }
        };
#endif //PIKUMAENGINE_INPUTSYSTEM_H

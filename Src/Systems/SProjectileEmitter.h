//
// Created by Manoloon on 03/09/2022.
//

#ifndef PIKUMAENGINE_SPROJECTILEEMITTER_H
#define PIKUMAENGINE_SPROJECTILEEMITTER_H

#include "ECS/ECS.h"
#include "ECS/EventBus.h"
#include "Components/Components.h"
#include "Events/KeyPressedEvent.h"

class SProjectileEmitter : public System
{

public:
    SProjectileEmitter();

    void SubscribeToEvent(std::unique_ptr<EventBus>& eventBus);

    void onKeyPressed(KeyPressedEvent& event);
 
    void Update(float DeltaTime,std::unique_ptr<Registry>& Registry);
};
#endif //PIKUMAENGINE_SPROJECTILEEMITTER_H

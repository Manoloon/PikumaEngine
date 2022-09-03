//
// Created by Manoloon on 31/07/2022.
//

#ifndef PIKUMAENGINE_SDAMAGE_H
#define PIKUMAENGINE_SDAMAGE_H

#include "../ECS/ECS.h"
#include "../ECS/EventBus.h"
#include "../Components/Components.h"
#include "../Events/CollisionEvent.h"

class SDamage : public System
{
public:
    SDamage()
    {
        RequireComponent<CBoxCollision>();
    }

    void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus)
    {
        eventBus->SubscribeToEvent<CollisionEvent>(this, &SDamage::onCollision);
    }

    void onCollision(CollisionEvent& event)
    {
        Logger::Warning("The damage system receive events entity" +
                std::to_string(event.entityA.GetId()) + "and entity" +
                std::to_string(event.entityB.GetId()));
        event.entityA.Destroy();
        event.entityB.Destroy();
    }

    void Update()
    {
        //Todo
    }
};
#endif //PIKUMAENGINE_SDAMAGE_H

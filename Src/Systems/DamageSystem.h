//
// Created by Manoloon on 31/07/2022.
//

#ifndef PIKUMAENGINE_DAMAGESYSTEM_H
#define PIKUMAENGINE_DAMAGESYSTEM_H

#include "../ECS/ECS.h"
#include "../ECS/EventBus.h"
#include "../Components/Components.h"
#include "../Events/CollisionEvent.h"

class DamageSystem : public System
{
public:
    DamageSystem()
    {
        RequireComponent<BoxCollisionComp>();
    }

    void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus)
    {
        eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::onCollision);
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
#endif //PIKUMAENGINE_DAMAGESYSTEM_H

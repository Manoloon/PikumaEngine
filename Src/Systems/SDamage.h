//
// Created by Manoloon on 31/07/2022.
//

#pragma once

#include "../ECS/ECS.h"
#include "../ECS/EventBus.h"
#include "../Components/Components.h"
#include "../Events/CollisionEvent.h"

class SDamage : public System
{
public:
    SDamage();

    void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus);

    void onCollision(CollisionEvent& event);

    void OnProjectileHitsOther(std::unique_ptr<Entity>& Projectile, std::unique_ptr<Entity>& Other);
};

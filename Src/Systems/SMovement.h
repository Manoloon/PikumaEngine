//
// Created by Manoloon on 26/05/2022.
//

#pragma once

#include "ECS/ECS.h"
#include "ECS/EventBus.h"
#include "Events/CollisionEvent.h"
#include "Components/Components.h"

class SMovement: public System
{
public:
    SMovement();

    void SubscribeToEvents(const std::unique_ptr<EventBus>& eventBus);

    void OnCollision(CollisionEvent& event);

    void OnEnemyHitsObstacle(Entity enemy, Entity obstacle);

    void Update(float DeltaTime);   
};

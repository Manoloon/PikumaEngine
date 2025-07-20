//
// Created by Manoloon on 28/07/2022.
//

#pragma once

#include "ECS/ECS.h"
#include "Event.h"

class CollisionEvent : public Event
{
public:
    Entity EntityA;
    Entity EntityB;
    explicit CollisionEvent(Entity entityA,Entity entityB)
                            :EntityA(entityA),EntityB(entityB){}
};

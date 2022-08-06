//
// Created by Manoloon on 28/07/2022.
//

#ifndef PIKUMAENGINE_COLLISIONEVENT_H
#define PIKUMAENGINE_COLLISIONEVENT_H

#include "../ECS/ECS.h"
#include "Event.h"

class CollisionEvent : public Event
{
public:
    Entity entityA;
    Entity entityB;
    explicit CollisionEvent(Entity entityA,Entity entityB)
                            :entityA(entityA),entityB(entityB){}
};


#endif //PIKUMAENGINE_COLLISIONEVENT_H

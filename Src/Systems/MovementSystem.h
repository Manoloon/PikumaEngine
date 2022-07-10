//
// Created by Manoloon on 26/05/2022.
//

#ifndef PIKUMAENGINE_MOVEMENTSYSTEM_H
#define PIKUMAENGINE_MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/Components.h"

class MovementSystem: public System
{
public:
    MovementSystem()
    {
        RequireComponent<TransformComp>();
        RequireComponent<RigidBodyComp>();
    }
    void Update(float DeltaTime)
    {
        for(auto entity : GetSystemEntities())
        {
        auto& transform = entity.GetComponent<TransformComp>();
        auto rigidBody = entity.GetComponent<RigidBodyComp>();

        transform.position.x += rigidBody.velocity.x * DeltaTime;
        transform.position.y += rigidBody.velocity.y * DeltaTime;
        }
    }
};
#endif //PIKUMAENGINE_MOVEMENTSYSTEM_H

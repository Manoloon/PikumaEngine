//
// Created by Manoloon on 26/05/2022.
//

#ifndef PIKUMAENGINE_SMOVEMENT_H
#define PIKUMAENGINE_SMOVEMENT_H

#include "../ECS/ECS.h"
#include "../Components/Components.h"

class SMovement: public System
{
public:
    SMovement()
    {
        RequireComponent<CTransform>();
        RequireComponent<CRigidBody>();
    }
    void Update(float DeltaTime)
    {
        for(auto entity : GetSystemEntities())
        {
        auto& transform = entity.GetComponent<CTransform>();
        auto rigidBody = entity.GetComponent<CRigidBody>();

        transform.position.x += rigidBody.velocity.x * DeltaTime;
        transform.position.y += rigidBody.velocity.y * DeltaTime;
        }
    }
};
#endif //PIKUMAENGINE_SMOVEMENT_H

//
// Created by Manoloon on 26/05/2022.
//

#pragma once

#include "../ECS/ECS.h"
#include "../Components/Components.h"

class SMovement: public System
{
    bool bBounce = false;
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

        bBounce = (transform.position.x < 0 || transform.position.x > Game::mapWidth ||
                  transform.position.y < 0 || transform.position.y > Game::mapHeight);
                  if(bBounce && !entity.HasTag("Player"))
                  {
                        entity.Destroy();
                  }
        }
    }
};

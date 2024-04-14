//
// Created by Manoloon on 26/05/2022.
//

#pragma once

#include "../ECS/ECS.h"
#include "../ECS/EventBus.h"
#include "../Events/CollisionEvent.h"
#include "../Components/Components.h"

class SMovement: public System
{
public:
    SMovement()
    {
        RequireComponent<CTransform>();
        RequireComponent<CRigidBody>();
    }

    void SubscribeToEvents(const std::unique_ptr<EventBus>& eventBus)
    {
        eventBus->SubscribeToEvent<CollisionEvent>(this, &SMovement::OnCollision);
    }

    void OnCollision(CollisionEvent& event)
    {
        Entity a = event.EntityA;
        Entity b = event.EntityB;

        if(a.BelongToGroup("Obstacles") && b.BelongToGroup("Enemies"))
        {
            OnEnemyHitsObstacle(a,b);
        }
        if(a.BelongToGroup("Enemies") && b.BelongToGroup("Obstacles"))
        {
            OnEnemyHitsObstacle(b,a);
        }
    }

    void OnEnemyHitsObstacle(Entity enemy, Entity obstacle)
    {
        if (enemy.HasComponent<CRigidBody>() && enemy.HasComponent<CSprite>()) {
                auto& rigidbody = enemy.GetComponent<CRigidBody>();
                auto& sprite = enemy.GetComponent<CSprite>();

                if (rigidbody.velocity.x != 0) {
                    rigidbody.velocity.x *= -1;
                    //TODO : FLIP
                    //sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
                }
                
                if (rigidbody.velocity.y != 0) {
                    rigidbody.velocity.y *= -1;
                   // sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
                }
            }
    }

    void Update(float DeltaTime)
    {
        for(auto entity : GetSystemEntities())
        {
        auto& transform = entity.GetComponent<CTransform>();
        auto& rigidBody = entity.GetComponent<CRigidBody>();


        transform.position.x += rigidBody.velocity.x * DeltaTime;
        transform.position.y += rigidBody.velocity.y * DeltaTime;

        bool bHitLimits = (transform.position.x < 0 || transform.position.x > Game::mapWidth ||
                            transform.position.y < 0 || transform.position.y > Game::mapHeight);
        
        if(bHitLimits && !entity.HasTag("Player"))
            {
                entity.Destroy();
            }
        }
    }       
};

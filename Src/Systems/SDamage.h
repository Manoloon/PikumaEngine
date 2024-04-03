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
        // SHOULD Change on event to return an uniqueptr
        std::unique_ptr<Entity> a = std::make_unique<Entity>(event.EntityA);
        std::unique_ptr<Entity> b = std::make_unique<Entity>(event.EntityB);

        if(a->BelongToGroup("projectiles") && b->HasTag("player"))
        {
            OnProjectileHitsOther(a,b);
        }
        if(b->BelongToGroup("projectiles") && a->HasTag("player"))
        {
            OnProjectileHitsOther(b,a);
        }
        // if(a.BelongToGroup("projectiles") && b.HasTag("enemies"))
        // {

        // }
        // if(b.BelongToGroup("projectiles") && a.HasTag("enemies"))
        // {

        // }
    }

    void OnProjectileHitsOther(std::unique_ptr<Entity>& Projectile, std::unique_ptr<Entity>& Other)
    {
        // std::unique_ptr<CShootEmitter> projectileComp = std::make_unique<CShootEmitter>(Projectile->GetComponent<CShootEmitter>());
        // if(projectileComp == nullptr)
        // {
        //     return;
        // }
        // if(!projectileComp->bIsFriendly)
        // {
        //     // auto& LocalHealth = Other.GetComponent<CHealth>();
        //     // LocalHealth.Health -= projectileComp.damagePercentage;

        //     // if(LocalHealth.Health <=0)
        //     // {
        //     //     Other.Destroy();
        //     // }
        //     // Projectile.Destroy();
        // }
    }
    void Update()
    {
        //Todo
    }
};

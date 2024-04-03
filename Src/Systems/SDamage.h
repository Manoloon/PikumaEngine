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
        Entity a = event.EntityA;
        Entity b = event.EntityB;

        if(a.BelongToGroup("projectiles") && b.HasTag("player"))
        {
            OnProjectileHitsOther(a,b);
        }
        if(b.BelongToGroup("projectiles") && a.HasTag("player"))
        {
            OnProjectileHitsOther(b,a);
        }
        if(a.BelongToGroup("projectiles") && b.HasTag("enemies"))
        {

        }
        if(b.BelongToGroup("projectiles") && a.HasTag("enemies"))
        {

        }
       // event.entityA.Destroy();

       // event.entityB.Destroy();
    }

    void OnProjectileHitsOther(Entity Projectile, Entity Other)
    {
        auto projectileComp = Projectile.GetComponent<CShootEmitter>();
        if(!projectileComp.bIsFriendly)
        {
            auto& LocalHealth = Other.GetComponent<CHealth>();
            LocalHealth.Health -= projectileComp.damagePercentage;

            if(LocalHealth.Health <=0)
            {
                Other.Destroy();
            }
            Projectile.Destroy();
        }
    }
    void Update()
    {
        //Todo
    }
};

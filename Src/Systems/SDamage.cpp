#include "SDamage.h"

SDamage::SDamage()
{
    RequireComponent<CBoxCollision>();
}

void SDamage::SubscribeToEvents(EventBus &eventBus)
{
    eventBus.SubscribeToEvent<CollisionEvent>(this, &SDamage::onCollision);
}

void SDamage::onCollision(CollisionEvent &event)
{
    // SHOULD Change on event to return an uniqueptr
    Entity a = event.EntityA;
    Entity b = event.EntityB;

    // Hit On Enemies
    // if(a.BelongToGroup("projectile") && b.HasComponent<CHealth>())
    // {
    //     OnProjectileHitsOther(a,b);
    // }
    // else if(a.HasComponent<CHealth>() && b.BelongToGroup("projectile"))
    // {
    //     OnProjectileHitsOther(b,a);
    // }
    if (a.BelongToGroup("projectile") && b.HasTag("player"))
    {
        OnProjectileHitsOther(a, b); // "a" is the projectile, "b" is the player
    }

    if (b.BelongToGroup("projectile") && a.HasTag("player"))
    {
        OnProjectileHitsOther(b, a); // "b" is the projectile, "a" is the player
    }

    if (a.BelongToGroup("projectile") && b.BelongToGroup("enemies"))
    {
        OnProjectileHitsOther(a, b); // "a" is the projectile, "b" is the enemy
    }

    if (b.BelongToGroup("projectile") && a.BelongToGroup("enemies"))
    {
        OnProjectileHitsOther(b, a); // "b" is the projectile, "a" is the enemy
    }
}

void SDamage::OnProjectileHitsOther(Entity Projectile, Entity Other)
{
    if (!Projectile.HasComponent<CProjectile>())
    {
        Logger::Warning("SDamage: OnProjectileHitsOther Projectile dont have CProjectile component");
        return;
    }
    const auto &projectileComp = Projectile.GetComponent<CProjectile>();
    if(Other.HasTag("player"))
    {
        if (!projectileComp.IsFriendly)
        {
            auto &healthComp = Other.GetComponent<CHealth>();

            healthComp.Health -= projectileComp.DamagePercent;
            if (Other.HasComponent<CTextComponent>())
            {
                Other.GetComponent<CTextComponent>().Text = std::to_string(healthComp.Health);
            }
            if (healthComp.Health < 1.0)
            {
                Logger::Error("SDamage:: player dead id: " + std::to_string(Other.GetId()));
                Other.Destroy();
            }
            Projectile.Destroy();
        }
    }
    else
    {
        if (projectileComp.IsFriendly && Other.HasComponent<CHealth>())
        {
            auto &healthComp = Other.GetComponent<CHealth>();

            healthComp.Health -= projectileComp.DamagePercent;
            if (Other.HasComponent<CTextComponent>())
            {
                Other.GetComponent<CTextComponent>().Text = std::to_string(healthComp.Health);
            }
            if (healthComp.Health < 1.0)
            {
                Logger::Error("SDamage:: Enemy dead id :" + std::to_string(Other.GetId()));
                Other.Destroy();
            }
            Projectile.Destroy();
        }
    }    
}
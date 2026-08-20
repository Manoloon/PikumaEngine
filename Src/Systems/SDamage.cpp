#include "SDamage.h"

SDamage::SDamage()
{
    RequireComponent<CBoxCollision>();
}
void SDamage::SubscribeToEvents(std::unique_ptr<EventBus> &eventBus)
{
    eventBus->SubscribeToEvent<CollisionEvent>(this, &SDamage::onCollision);
}

void SDamage::onCollision(CollisionEvent &event)
{
    // SHOULD Change on event to return an uniqueptr
    std::unique_ptr<Entity> a = std::make_unique<Entity>(event.EntityA);
    std::unique_ptr<Entity> b = std::make_unique<Entity>(event.EntityB);
    // Hit On Enemies
    if(a->BelongToGroup("projectiles") && b->HasComponent<CHealth>())
    {
        OnProjectileHitsOther(a,b);
    }
    else if(a->HasComponent<CHealth>() && b->BelongToGroup("projectiles"))
    {
        OnProjectileHitsOther(b,a);
    }
}

void SDamage::OnProjectileHitsOther(std::unique_ptr<Entity> &Projectile, std::unique_ptr<Entity> &Other)
{
    if(!Projectile->HasComponent<CShootEmitter>())
    {
        Logger::Warning("SDamage: OnProjectileHitsOther Projectile dont have CSHootEmitter component");
        return;
    }
    std::unique_ptr<CShootEmitter> projectileComp = std::make_unique<CShootEmitter>(Projectile->GetComponent<CShootEmitter>());

    if (!projectileComp->bIsFriendly)
    {
        auto &LocalHealth = Other->GetComponent<CHealth>();

        LocalHealth.Health -= projectileComp->damagePercentage;
        if(Other->HasComponent<CTextComponent>())
        {
            Other->GetComponent<CTextComponent>().Text = std::to_string(LocalHealth.Health);
        }
        if (LocalHealth.Health <= 0)
        {
            Other->Destroy();
        }
        Projectile->Destroy();
    }
}
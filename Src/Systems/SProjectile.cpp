#include "SProjectile.h"

SProjectile::SProjectile()
{
    RequireComponent<CProjectile>();
}

void SProjectile::Update(float DeltaTime)
{
    for(auto& entity : GetSystemEntities())
    {
        auto& projectile = entity.GetComponent<CProjectile>();
        projectile.LifeTime +=DeltaTime;
        if(projectile.LifeTime > projectile.LifeSpan)
        {
            entity.Destroy();
        }
    }
}

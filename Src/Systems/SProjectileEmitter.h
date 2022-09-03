//
// Created by Manoloon on 03/09/2022.
//

#ifndef PIKUMAENGINE_SPROJECTILEEMITTER_H
#define PIKUMAENGINE_SPROJECTILEEMITTER_H

#include "../ECS/ECS.h"
#include "../Components/Components.h"

class SProjectileEmitter : public System
{
public:
    SProjectileEmitter()
    {
        RequireComponent<CShootEmitter>();
        RequireComponent<CTransform>();
    }
    void Update(float DeltaTime,std::unique_ptr<Registry>& Registry)
    {
        for(auto entity : GetSystemEntities())
        {
            auto& shootEmitter = entity.GetComponent<CShootEmitter>();
            const auto& transform = entity.GetComponent<CTransform>();
            if((DeltaTime - shootEmitter.lastEmissionTime) > shootEmitter.loopFrequency)
            {
                auto projectilePosition = transform.position;
                if(entity.HasComponent<CSprite>())
                {
                    const auto Sprite = entity.GetComponent<CSprite>();
                    projectilePosition.x += (transform.scale.x * Sprite.spriteRect.width/2);
                    projectilePosition.y += (transform.scale.y * Sprite.spriteRect.height/2);
                }
                Entity projectile = Registry->CreateEntity();
                Logger::Warning("Shoot");
                projectile.AddComponent<CTransform>(projectilePosition,transform.scale,transform
                .rotation);
                projectile.AddComponent<CRigidBody>(shootEmitter.velocity);
                projectile.AddComponent<CSprite>("bullet-image",sf::Vector2f(4.f, 4.f),
                                                 ERenderLayers::LAYER_PROJECTILE);
                projectile.AddComponent<CBoxCollision>(sf::Vector2f(4.f, 4.f));

                shootEmitter.lastEmissionTime = DeltaTime;
            }
        }
    }
};
#endif //PIKUMAENGINE_SPROJECTILEEMITTER_H

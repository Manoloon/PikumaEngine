//
// Created by Manoloon on 03/09/2022.
//

#ifndef PIKUMAENGINE_SPROJECTILEEMITTER_H
#define PIKUMAENGINE_SPROJECTILEEMITTER_H

#include "../ECS/ECS.h"
#include "../Components/Components.h"
#include "../Events/ShootEvent.h"

class SProjectileEmitter : public System
{
public:
    SProjectileEmitter()
    {
        RequireComponent<CShootEmitter>();
        RequireComponent<CTransform>();
    }

    void SubscribeToEvent(std::unique_ptr<EventBus>& eventBus)
    {
        eventBus->SubscribeToEvent<ShootEvent>(this, &SProjectileEmitter::onKeyPressed);
    }

    void onKeyPressed(ShootEvent& event)
    {
        Logger::Warning("Shoot");

        if(event.keyCode == sf::Keyboard::Space)
        {
            for(auto entity : GetSystemEntities())
            {
                if(entity.HasComponent<CCameraFollow>())
                {
                    auto& shootEmitter = entity.GetComponent<CShootEmitter>();
                    const auto& transform = entity.GetComponent<CTransform>();
                    const auto& rigidBody = entity.GetComponent<CRigidBody>();
                    auto projectilePosition = transform.position;
                    if(entity.HasComponent<CSprite>())
                    {
                        const auto& Sprite = entity.GetComponent<CSprite>();
                        projectilePosition.x += (transform.scale.x * Sprite.spriteRect.width/2);
                        projectilePosition.y += (transform.scale.y * Sprite.spriteRect.height/2);
                    }
                    // set projectileVelocity due to direction of player
                    sf::Vector2f projectileVelocity = shootEmitter.velocity;
                    int dirX=0;
                    int dirY = 0;
                    rigidBody.velocity.x >= 0 ? dirX =1 : dirX =-1;
                    rigidBody.velocity.y >= 0 ? dirY = 1 : dirY =-1;
                    projectileVelocity.x = shootEmitter.velocity.x * dirX;
                    projectileVelocity.y = shootEmitter.velocity.y * dirY;
                  //create projectile
                    Entity projectile = entity.registry->CreateEntity();
                    projectile.AddComponent<CTransform>(projectilePosition,transform.scale,transform
                            .rotation);
                    projectile.AddComponent<CRigidBody>(projectileVelocity);
                    projectile.AddComponent<CSprite>("bullet-image",sf::Vector2f(4.f, 4.f),
                                                     ERenderLayers::LAYER_PROJECTILE);
                    projectile.AddComponent<CBoxCollision>(sf::Vector2f(4.f, 4.f));
                    shootEmitter.lastEmissionTime = 0;
                }
            }
        }
    }
    void Update(int DeltaTime,std::unique_ptr<Registry>& Registry)
    {
        for(auto entity : GetSystemEntities())
        {
            auto& shootEmitter = entity.GetComponent<CShootEmitter>();
            const auto& transform = entity.GetComponent<CTransform>();
            shootEmitter.lastEmissionTime +=DeltaTime;
            if(shootEmitter.loopFrequency == 0)
            {
                continue;
            }
            // timer execute
            if( shootEmitter.lastEmissionTime > shootEmitter.loopFrequency)
            {
                auto projectilePosition = transform.position;
                if(entity.HasComponent<CSprite>())
                {
                    const auto& Sprite = entity.GetComponent<CSprite>();
                    projectilePosition.x += (transform.scale.x * Sprite.spriteRect.width/2);
                    projectilePosition.y += (transform.scale.y * Sprite.spriteRect.height/2);
                }
                Entity projectile = Registry->CreateEntity();
                projectile.AddComponent<CTransform>(projectilePosition,transform.scale,transform
                .rotation);
                projectile.AddComponent<CRigidBody>(shootEmitter.velocity);
                projectile.AddComponent<CSprite>("bullet-image",sf::Vector2f(4.f, 4.f),
                                                 ERenderLayers::LAYER_PROJECTILE);
                projectile.AddComponent<CBoxCollision>(sf::Vector2f(4.f, 4.f));
                shootEmitter.lastEmissionTime = 0;
            }
        }
    }
};
#endif //PIKUMAENGINE_SPROJECTILEEMITTER_H

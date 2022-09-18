//
// Created by Manoloon on 03/09/2022.
//

#ifndef PIKUMAENGINE_SPROJECTILEEMITTER_H
#define PIKUMAENGINE_SPROJECTILEEMITTER_H

#include "../ECS/ECS.h"
#include "../Components/Components.h"
#include "../Events/KeyPressedEvent.h"

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
        eventBus->SubscribeToEvent<KeyPressedEvent>(this, &SProjectileEmitter::onKeyPressed);
    }

    void onKeyPressed(KeyPressedEvent& event)
    {
        Logger::Warning("Shoot");

        if(event.keySymbol == sf::Keyboard::Space)
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
                    int dirX = 0;
                    int dirY = 0;
                    if(rigidBody.velocity.x !=0)
                    {
                        rigidBody.velocity.x > 0 ? dirX =1 : dirX =-1;
                    }
                    else
                    {
                        dirX = 0;
                    }
                    if(rigidBody.velocity.y != 0)
                    {
                        rigidBody.velocity.y > 0 ? dirY = 1 : dirY =-1;
                    }
                    else
                    {
                        dirY = 0;
                    }
                    projectileVelocity.x = shootEmitter.velocity.x * dirX;
                    projectileVelocity.y = shootEmitter.velocity.y * dirY;
                  //create projectile
                    Entity projectile = entity.registry->CreateEntity();
                    projectile.Tag("projectile");
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
                projectile.Tag("projectile");
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

#include "SProjectileEmitter.h"

SProjectileEmitter::SProjectileEmitter() 
{
    RequireComponent<CShootEmitter>();
    RequireComponent<CTransform>();
}

void SProjectileEmitter::SubscribeToEvent(std::unique_ptr<EventBus>& eventBus)
{
    eventBus->SubscribeToEvent<KeyPressedEvent>(this, &SProjectileEmitter::onKeyPressed);
}

void SProjectileEmitter::onKeyPressed(KeyPressedEvent& event)
{
        if(event.KeySymbol == sf::Keyboard::Space)
        {
            for(auto entity : GetSystemEntities())
            {
                if(entity.HasTag("Player"))
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
                    if(projectileVelocity.x != 0)
                        {
                        if (rigidBody.velocity.x >= 0) dirX = +1;
                        if (rigidBody.velocity.x < 0) dirX = -1;
                        }
                    if(projectileVelocity.y != 0)
                        {
                        if (rigidBody.velocity.y >= 0) dirY = +1;
                        if (rigidBody.velocity.y < 0) dirY = -1;
                        }
                    else
                        {
                        dirY = 0;
                        }
                    
                    // if(rigidBody.velocity.x !=0)
                    // {
                    //     rigidBody.velocity.x > 0 ? dirX = 1 : dirX = -1;
                    // }
                    // else
                    // {
                    //     dirX = 0;
                    // }
                    // if(rigidBody.velocity.y != 0)
                    // {
                    //     rigidBody.velocity.y > 0 ? dirY = 1 : dirY = -1;
                    // }
                    // else
                    // {
                    //     dirY = 0;
                    // }
                    std::cout << "X dir : " << dirX << " : " << " Y Dir : " << dirY << std::endl;
                    projectileVelocity.x = shootEmitter.velocity.x * dirX;
                    projectileVelocity.y = shootEmitter.velocity.y * dirY;
                  //create projectile
                    Entity projectile = entity.registry->CreateEntity();
                    projectile.Group("projectiles");
                    projectile.AddComponent<CTransform>(projectilePosition,transform.scale,transform.rotation);
                    projectile.AddComponent<CRigidBody>(projectileVelocity);
                    projectile.AddComponent<CSprite>("bullet-image",transform.scale,ERenderLayers::L_PROJECTILE);
                    projectile.AddComponent<CBoxCollision>(transform.scale);
                    projectile.AddComponent<CShootEmitter>(projectileVelocity,0,
                    shootEmitter.lifeSpan,shootEmitter.damagePercentage,
                    shootEmitter.bIsFriendly,shootEmitter.lastEmissionTime);
                }
            }
        }
}

void SProjectileEmitter::Update(int DeltaTime, std::unique_ptr<Registry> &Registry) 
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
                projectile.Group("projectiles");
                projectile.AddComponent<CTransform>(projectilePosition,transform.scale,transform
                .rotation);
                projectile.AddComponent<CRigidBody>(shootEmitter.velocity);
                projectile.AddComponent<CSprite>("bullet-image",sf::Vector2f(4.f, 4.f),
                                                 ERenderLayers::L_PROJECTILE);
                projectile.AddComponent<CBoxCollision>(sf::Vector2f(4.f, 4.f));
                shootEmitter.lastEmissionTime = 0;
            }
    }
}

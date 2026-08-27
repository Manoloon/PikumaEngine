#include "SProjectileEmitter.h"

SProjectileEmitter::SProjectileEmitter()
{
    RequireComponent<CShootEmitter>();
    RequireComponent<CTransform>();
}

void SProjectileEmitter::SubscribeToEvent(EventBus &eventBus)
{
    eventBus.SubscribeToEvent<KeyPressedEvent>(this, &SProjectileEmitter::onKeyPressed);
}

void SProjectileEmitter::onKeyPressed(KeyPressedEvent &event)
{
    if (event.KeySymbol != sf::Keyboard::Key::Space)
        return;

    for (auto entity : GetSystemEntities())
    {
        if (entity.HasTag("player") && entity.HasComponent<CKeyboardControlled>())
        {
            CShootEmitter &shootEmitter = entity.GetComponent<CShootEmitter>();
            const CTransform &transform = entity.GetComponent<CTransform>();
            const auto& keyboard = entity.GetComponent<CKeyboardControlled>();
            sf::Vector2f projectilePosition = transform.position;

            // Determine direction from rigidbody
            sf::Vector2f dir = keyboard.facingDirection;
            if (entity.HasComponent<CSprite>())
            {
                const CSprite &Sprite = entity.GetComponent<CSprite>();
                sf::Vector2f playerSize = {Sprite.spriteRect.size.x * transform.scale.x,
                                           Sprite.spriteRect.size.y * transform.scale.y};
                sf::Vector2f playerCenter = transform.position + playerSize / 2.f;
                projectilePosition = playerCenter + dir * 32.0f;
            }

            sf::Vector2f projectileVelocity = shootEmitter.velocity.length() * dir;
            if(shootEmitter.lastEmissionTime < shootEmitter.loopFrequency)
            {
                return;
            }
            //create projectile
            Entity projectile = entity.registry->CreateEntity();
            const sf::Vector2f projectileScale = {4.f, 4.f};
            const sf::Vector2f projectileCollisionSize = {4.f, 4.f};
            projectile.Group("projectile");
            projectile.AddComponent<CTransform>(projectilePosition, projectileScale, transform.rotation);
            projectile.AddComponent<CRigidBody>(projectileVelocity);
            projectile.AddComponent<CSprite>("bullet-texture", projectileScale, ERenderLayers::L_PROJECTILE);
            projectile.AddComponent<CBoxCollision>(projectileCollisionSize);
            projectile.AddComponent<CProjectile>(shootEmitter.bIsFriendly,
                                                   shootEmitter.damagePercentage,
                                                   shootEmitter.lifeSpan);
            break;
        }
    }
}

void SProjectileEmitter::Update(float DeltaTime, Registry &Registry)
{
    for (auto entity : GetSystemEntities())
    {
        CShootEmitter &shootEmitter = entity.GetComponent<CShootEmitter>();
        shootEmitter.lastEmissionTime += DeltaTime;
        if(shootEmitter.loopFrequency == 0)
        {
            //Logger::Warning("Entity ID : " + std::to_string(entity.GetId()) + "loopFrequency = 0");
            continue;
        }
        if (shootEmitter.lastEmissionTime < shootEmitter.loopFrequency)
        {
            //Logger::Warning("Entity ID : " + std::to_string(entity.GetId()) + " emissionTime " + std::to_string(shootEmitter.lastEmissionTime) + " <=" + std::to_string(shootEmitter.loopFrequency));
            continue;
        }
        const CTransform &transform = entity.GetComponent<CTransform>();
        auto projectilePosition = transform.position;
        if (entity.HasComponent<CSprite>())
        {
            const CSprite &Sprite = entity.GetComponent<CSprite>();
            projectilePosition.x += transform.scale.x * Sprite.spriteRect.size.x * 0.5f;
            projectilePosition.y += transform.scale.y * Sprite.spriteRect.size.y * 0.5f;
        }
        if(entity.HasTag("player"))
        {
            continue;
        }
           
        Entity projectile = Registry.CreateEntity();
        // TODO : this should be in an enum
        projectile.Group("projectile");
        projectile.AddComponent<CTransform>(projectilePosition, transform.scale, transform.rotation);
        projectile.AddComponent<CRigidBody>(shootEmitter.velocity);
        projectile.AddComponent<CSprite>("bullet-texture", sf::Vector2f(4.f, 4.f), ERenderLayers::L_PROJECTILE);
        projectile.AddComponent<CBoxCollision>(sf::Vector2f(4.f, 4.f));
        projectile.AddComponent<CProjectile>(shootEmitter.bIsFriendly,
                                            shootEmitter.damagePercentage,
                                            shootEmitter.lifeSpan);
    // reset the emission.
    shootEmitter.lastEmissionTime -= shootEmitter.loopFrequency;
    }
}

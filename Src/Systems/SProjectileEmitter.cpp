#include "SProjectileEmitter.h"

SProjectileEmitter::SProjectileEmitter()
{
    RequireComponent<CShootEmitter>();
    RequireComponent<CTransform>();
}

void SProjectileEmitter::SubscribeToEvent(std::unique_ptr<EventBus> &eventBus)
{
    eventBus->SubscribeToEvent<KeyPressedEvent>(this, &SProjectileEmitter::onKeyPressed);
}

void SProjectileEmitter::onKeyPressed(KeyPressedEvent &event)
{
    if (event.KeySymbol != sf::Keyboard::Key::Space)
        return;

    for (auto entity : GetSystemEntities())
    {
        if (entity.HasTag("Player"))
        {
            CShootEmitter &shootEmitter = entity.GetComponent<CShootEmitter>();
            const CTransform &transform = entity.GetComponent<CTransform>();
            //const CRigidBody &rigidBody = entity.GetComponent<CRigidBody>();
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
            
            //create projectile
            Entity projectile = entity.registry->CreateEntity();
            const sf::Vector2f projectileScale = {2.f, 2.f};
            const sf::Vector2f projectileCollisionSize = {8.f, 8.f};
            projectile.Group("projectile");
            projectile.AddComponent<CTransform>(projectilePosition, projectileScale, transform.rotation);
            projectile.AddComponent<CRigidBody>(projectileVelocity);
            projectile.AddComponent<CSprite>("bullet-texture", projectileScale, ERenderLayers::L_PROJECTILE);
            projectile.AddComponent<CBoxCollision>(projectileCollisionSize);
            projectile.AddComponent<CShootEmitter>(projectileVelocity,
                                                   0,
                                                   shootEmitter.lifeSpan,
                                                   shootEmitter.damagePercentage,
                                                   shootEmitter.bIsFriendly,
                                                   shootEmitter.lastEmissionTime);
            break;
        }
    }
}

void SProjectileEmitter::Update(float DeltaTime, std::unique_ptr<Registry> &Registry)
{
    for (auto entity : GetSystemEntities())
    {
        CShootEmitter &shootEmitter = entity.GetComponent<CShootEmitter>();
        const CTransform &transform = entity.GetComponent<CTransform>();
        shootEmitter.lastEmissionTime += DeltaTime;
        if (shootEmitter.loopFrequency == 0 || shootEmitter.lastEmissionTime < shootEmitter.loopFrequency)
        {
            continue;
        }
        auto projectilePosition = transform.position;
        if (entity.HasComponent<CSprite>())
        {
            const CSprite &Sprite = entity.GetComponent<CSprite>();
            projectilePosition.x += transform.scale.x * Sprite.spriteRect.size.x * 0.5f;
            projectilePosition.y += transform.scale.y * Sprite.spriteRect.size.y * 0.5f;
        }
        // TODO : Ver esto if(entity.BelongToGroup())
        // if(entity.HasTag("Player")) return;
        // Entity projectile = Registry->CreateEntity();
        // // TODO : this should be in an enum
        // projectile.Group("projectile");
        // projectile.AddComponent<CTransform>(projectilePosition, transform.scale, transform.rotation);
        // projectile.AddComponent<CRigidBody>(shootEmitter.velocity);
        // projectile.AddComponent<CSprite>("bullet-texture", sf::Vector2f(4.f, 4.f), ERenderLayers::L_PROJECTILE);
        // projectile.AddComponent<CBoxCollision>(sf::Vector2f(4.f, 4.f));
        // shootEmitter.lastEmissionTime = 0.f;
    }
}

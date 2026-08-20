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
        if (!entity.HasTag("Player"))
            continue;

        CShootEmitter &shootEmitter = entity.GetComponent<CShootEmitter>();
        const CTransform &transform = entity.GetComponent<CTransform>();
        const CRigidBody &rigidBody = entity.GetComponent<CRigidBody>();
        sf::Vector2f projectilePosition = transform.position;
        if (entity.HasComponent<CSprite>())
        {
            const CSprite &Sprite = entity.GetComponent<CSprite>();
            projectilePosition.x += transform.scale.x * Sprite.spriteRect.size.x * 0.5f;
            projectilePosition.y += transform.scale.y * Sprite.spriteRect.size.y * 0.5f;
        }
        // Determine direction from rigidbody
        sf::Vector2f dir = {1.f, 0.f};
        if (rigidBody.velocity.x != 0.f)
            dir.x = (rigidBody.velocity.x > 0.f) ? 1.f : -1.f;
        if (rigidBody.velocity.y != 0.f)
            dir.y = (rigidBody.velocity.y > 0.f) ? 1.f : -1.f;

        if (dir == sf::Vector2f(0.f, 0.f))
            dir.x = 1.f; // default shot dir

        sf::Vector2f projectileVelocity = {shootEmitter.velocity.x * dir.x, shootEmitter.velocity.y * dir.y};
        //create projectile
        Entity projectile = entity.registry->CreateEntity();
        projectile.Group("projectiles");
        projectile.AddComponent<CTransform>(projectilePosition, transform.scale, transform.rotation);
        projectile.AddComponent<CRigidBody>(projectileVelocity);
        projectile.AddComponent<CSprite>("bullet-image", transform.scale, ERenderLayers::L_PROJECTILE);
        projectile.AddComponent<CBoxCollision>(transform.scale);
        projectile.AddComponent<CShootEmitter>(projectileVelocity,
                                               0,
                                               shootEmitter.lifeSpan,
                                               shootEmitter.damagePercentage,
                                               shootEmitter.bIsFriendly,
                                               shootEmitter.lastEmissionTime);
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
        // Entity projectile = Registry->CreateEntity();
        // // TODO : this should be in an enum
        // projectile.Group("projectiles");
        // projectile.AddComponent<CTransform>(projectilePosition, transform.scale, transform.rotation);
        // projectile.AddComponent<CRigidBody>(shootEmitter.velocity);
        // projectile.AddComponent<CSprite>("bullet-image", sf::Vector2f(4.f, 4.f), ERenderLayers::L_PROJECTILE);
        // projectile.AddComponent<CBoxCollision>(sf::Vector2f(4.f, 4.f));
        // shootEmitter.lastEmissionTime = 0.f;
    }
}

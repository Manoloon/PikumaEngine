#include "SMovement.h"
#include "Game.h"

SMovement::SMovement()
{
    RequireComponent<CTransform>();
    RequireComponent<CRigidBody>();
}

void SMovement::SubscribeToEvents(const std::unique_ptr<EventBus> &eventBus)
{
    eventBus->SubscribeToEvent<CollisionEvent>(this, &SMovement::OnCollision);
}

void SMovement::OnCollision(CollisionEvent &event)
{
    Entity a = event.EntityA;
    Entity b = event.EntityB;

    if (a.BelongToGroup("Obstacles") && b.BelongToGroup("Enemies"))
    {
        OnEnemyHitsObstacle(a, b);
    }
    if (a.BelongToGroup("Enemies") && b.BelongToGroup("Obstacles"))
    {
        OnEnemyHitsObstacle(b, a);
    }
}

void SMovement::OnEnemyHitsObstacle(Entity enemy, Entity obstacle)
{
    if (enemy.HasComponent<CRigidBody>() && enemy.HasComponent<CSprite>())
    {
        auto &rigidbody = enemy.GetComponent<CRigidBody>();
        auto &sprite = enemy.GetComponent<CSprite>();

        if (rigidbody.velocity.x != 0)
        {
            rigidbody.velocity.x *= -1;
            //TODO : FLIP
            //sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        }

        if (rigidbody.velocity.y != 0)
        {
            rigidbody.velocity.y *= -1;
            // sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
        }
    }
}

void SMovement::Update(float DeltaTime)
{
    for (auto entity : GetSystemEntities())
    {
        auto &transform = entity.GetComponent<CTransform>();
        auto &rigidBody = entity.GetComponent<CRigidBody>();

        if (entity.HasTag("Player"))
        {
            const auto &keyboard = entity.GetComponent<CKeyboardControlled>();
            const auto &input = keyboard.inputDirection;

            if (input.lengthSquared() > 0.f)
            {
                rigidBody.velocity += input * keyboard.acceleration * DeltaTime;

                const float maxSpeedSquared = keyboard.maxSpeed * keyboard.maxSpeed;
                if (rigidBody.velocity.lengthSquared() > maxSpeedSquared)
                {
                    rigidBody.velocity = rigidBody.velocity.normalized() * keyboard.maxSpeed;
                }
            }
            else
            {
                rigidBody.velocity *= std::pow(keyboard.damping, DeltaTime * 60.f);
                if (rigidBody.velocity.lengthSquared() < 0.01f)
                {
                    rigidBody.velocity = {0.f, 0.f};
                }
            }
            transform.position += rigidBody.velocity * DeltaTime;
            // check bounds
            const auto& sprite = entity.GetComponent<CSprite>();
            const float entityWidth = sprite.spriteRect.size.x * transform.scale.x;
            const float entityHeight = sprite.spriteRect.size.y * transform.scale.y;

            transform.position.x = std::clamp(transform.position.x,0.f,Game::mapWidth - entityWidth);
            transform.position.y = std::clamp(transform.position.y,0.f,Game::mapHeight - entityHeight);
            // Stop velocity when hitting the boundary
            if (transform.position.x <= 0.f ||
                transform.position.x >= Game::mapWidth - entityWidth)
            {
                rigidBody.velocity.x = 0.f;
            }

            if (transform.position.y <= 0.f ||
                transform.position.y >= Game::mapHeight - entityHeight)
            {
                rigidBody.velocity.y = 0.f;
            }
            continue;
        }
        transform.position.x += rigidBody.velocity.x * DeltaTime;
        transform.position.y += rigidBody.velocity.y * DeltaTime;

        bool bOutOfBounds = (transform.position.x < 0 || transform.position.x > Game::mapWidth ||
                             transform.position.y < 0 || transform.position.y > Game::mapHeight);

        if (bOutOfBounds && entity.HasTag("projectile"))
        {
            entity.Destroy();
        }
    }
}

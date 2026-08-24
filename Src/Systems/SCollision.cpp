#include "SCollision.h"
#include "Events/Event.h"

SCollision::SCollision()
{
    RequireComponent<CTransform>();
    RequireComponent<CBoxCollision>();
}

bool SCollision::CheckAABBCollision(const sf::Vector2f &aPos,
                                    const sf::Vector2f &aSize,
                                    const sf::Vector2f &bPos,
                                    const sf::Vector2f &bSize) const
{
    return (
        aPos.x < bPos.x + bSize.x && 
        aPos.x + aSize.x > bPos.x && 
        aPos.y < bPos.y + bSize.y &&
        aPos.y + aSize.y > bPos.y);
}

void SCollision::Update([[maybe_unused]] float DeltaTime, std::unique_ptr<EventBus> &eventBus)
{
    auto Entities = GetSystemEntities();
    for (auto i = Entities.begin(); i != Entities.end(); ++i)
    {
        auto entityA = *i;
        const auto &aTransform = entityA.GetComponent<CTransform>();
        const auto &aCollision = entityA.GetComponent<CBoxCollision>();

        for (auto j = std::next(i); j != Entities.end(); ++j)
        {
            auto entityB = *j;
            const auto &bTransform = entityB.GetComponent<CTransform>();
            const auto &bCollision = entityB.GetComponent<CBoxCollision>();

            // check collision
            if (CheckAABBCollision(aTransform.position + aCollision.offset, aCollision.size, bTransform.position + bCollision.offset, bCollision.size))
            {
                //Logger::Info("SCollision : Update : Entity " + std::to_string(entityA.GetId()) + " collided with entity " + std::to_string(entityB.GetId()));
                HitColor = sf::Color::Red;
                eventBus->EmitEvent<CollisionEvent>(entityA, entityB);
            }
        }
    }
}

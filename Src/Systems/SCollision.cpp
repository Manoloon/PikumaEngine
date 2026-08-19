#include "SCollision.h"

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
    return (aPos.x < bPos.x + bSize.x && aPos.x + aSize.x > bPos.x && aPos.y < bPos.y + bSize.y &&
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
        std::vector<Entity>::iterator j = i;
        ++j;
        for (; j != Entities.end(); ++j)
        {
            auto entityB = *j;
            const auto &bTransform = entityB.GetComponent<CTransform>();
            const auto &bCollision = entityB.GetComponent<CBoxCollision>();
            if (i == j)
            {
                continue;
            }
            if (CheckAABBCollision(aTransform.position, aCollision.size, bTransform.position, bCollision.size))
            {
                HitColor = sf::Color::Red;
                eventBus->EmitEvent<CollisionEvent>(entityA, entityB);
            }
            else
            {
                HitColor = sf::Color::Green;
            }
        }
    }
}

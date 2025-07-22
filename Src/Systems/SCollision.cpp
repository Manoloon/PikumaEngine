#include "SCollision.h"

SCollision::SCollision() 
{
        RequireComponent<CTransform>();
        RequireComponent<CBoxCollision>();
}

bool SCollision::CheckAABBCollision(const sf::Vector2f &aPosition,
                                    const sf::Vector2f &aCollisionScale,
                                    const sf::Vector2f &bPosition,
                                    const sf::Vector2f &bCollisionScale) const 
                                    {
    float aHorArea = aPosition.x + aCollisionScale.x;
    float bHorArea = bPosition.x + bCollisionScale.x;
    float aVerArea = aPosition.y + aCollisionScale.y;
    float bVerArea = bPosition.y + bCollisionScale.y;
    return (aPosition.x < bHorArea &&
            aHorArea > bPosition.x &&
            aPosition.y < bVerArea &&
            aVerArea > bPosition.y);
}

void SCollision::Update(float DeltaTime, std::unique_ptr<EventBus> &eventBus) 
{
    auto Entities = GetSystemEntities();
      for(auto i = Entities.begin(); i != Entities.end(); i++)
      {
          auto entityA = *i;
          const auto& aTransform = entityA.GetComponent<CTransform>();
          const auto& aCollision = entityA.GetComponent<CBoxCollision>();
          for(auto j=i;j!=Entities.end();j++)
          {
              auto entityB = *j;
              const auto& bTransform = entityB.GetComponent<CTransform>();
              const auto& bCollision = entityB.GetComponent<CBoxCollision>();
              if(i == j){ continue;}
              if(CheckAABBCollision(aTransform.position,
                                    aCollision.size,
                                            bTransform.position,
                                    bCollision.size))
              {
                  HitColor = sf::Color::Red;
                  eventBus->EmitEvent<CollisionEvent>(entityA,entityB);
              }
              else
              {
                  HitColor = sf::Color::Green;
              }
          }
      }
}

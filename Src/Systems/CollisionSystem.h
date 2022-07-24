//
// Created by Manoloon on 23/07/2022.
//

#ifndef PIKUMAENGINE_COLLISIONSYSTEM_H
#define PIKUMAENGINE_COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/Components.h"

class CollisionSystem: public System
{
bool CheckAABBCollision(const sf::Vector2f& aPosition,
                        const sf::Vector2f& aCollisionScale,
                        const sf::Vector2f& bPosition,
                        const sf::Vector2f& bCollisionScale) const
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
public:
    CollisionSystem()
    {
        RequireComponent<TransformComp>();
        RequireComponent<BoxCollisionComp>();
    }
    void Update(float DeltaTime)
    {
      //check all entities that have a boxCollider
      //to see if they are colliding with each other
      auto entities = GetSystemEntities();
      for(auto i = entities.begin(); i != entities.end(); i++)
      {
          auto entityA = *i;
          const auto& aTransform = entityA.GetComponent<TransformComp>();
          const auto& aCollision = entityA.GetComponent<BoxCollisionComp>();
          for(auto j=i;j!=entities.end();j++)
          {
              auto EntityB = *j;
              const auto& bTransform = EntityB.GetComponent<TransformComp>();
              const auto& bCollision = EntityB.GetComponent<BoxCollisionComp>();
              if(i == j){ continue;}
              if(CheckAABBCollision(aTransform.position,
                                    aCollision.size,
                                    bTransform.position,
                                    bCollision.size))
              {
                  Logger::Warning("Colliding :" + std::to_string(EntityB.GetId()) + "With : " +
                  std::to_string(entityA.GetId()));
              }
          }
      }
    }
};
#endif //PIKUMAENGINE_COLLISIONSYSTEM_H

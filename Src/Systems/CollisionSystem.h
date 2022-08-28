//
// Created by Manoloon on 23/07/2022.
//

#ifndef PIKUMAENGINE_COLLISIONSYSTEM_H
#define PIKUMAENGINE_COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/Components.h"
#include "../Events/CollisionEvent.h"

class CollisionSystem: public System
{
[[nodiscard]] bool CheckAABBCollision(const sf::Vector2f& aPosition,
                                      const sf::Vector2f& aCollisionScale,
                                      const sf::Vector2f& bPosition,
                                      const sf::Vector2f& bCollisionScale)  const
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
    sf::Color HitColor = sf::Color::Green;
public:
    CollisionSystem()
    {
        RequireComponent<TransformComp>();
        RequireComponent<BoxCollisionComp>();
    }
    [[nodiscard]] sf::Color GetHitColor()const{return HitColor;}

    void Update([[maybe_unused]] float DeltaTime,std::unique_ptr<EventBus>& eventBus)
    {
      auto entities = GetSystemEntities();
      for(auto i = entities.begin(); i != entities.end(); i++)
      {
          auto entityA = *i;
          const auto& aTransform = entityA.GetComponent<TransformComp>();
          const auto& aCollision = entityA.GetComponent<BoxCollisionComp>();
          for(auto j=i;j!=entities.end();j++)
          {
              auto entityB = *j;
              const auto& bTransform = entityB.GetComponent<TransformComp>();
              const auto& bCollision = entityB.GetComponent<BoxCollisionComp>();
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
};
#endif //PIKUMAENGINE_COLLISIONSYSTEM_H

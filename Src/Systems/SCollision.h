//
// Created by Manoloon on 23/07/2022.
//
#pragma once

#include "ECS/EventBus.h"
#include "Components/Components.h"
#include "Events/CollisionEvent.h"
#include "ECS/ECS.h"

class SCollision: public System
{

public:
    SCollision();
private:
[[nodiscard]] bool CheckAABBCollision(const sf::Vector2f& aPosition,
                                      const sf::Vector2f& aCollisionScale,
                                      const sf::Vector2f& bPosition,
                                      const sf::Vector2f& bCollisionScale)  const;
    sf::Color HitColor = sf::Color::Green;

public:

    [[nodiscard]] sf::Color GetHitColor()const{return HitColor;}
    /**
    * \param DeltaTime Delta Time in Milliseconds.
    * \param eventBus eventBus pointer
    */
    void Update(EventBus& eventBus);
};

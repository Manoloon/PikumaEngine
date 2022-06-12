//
// Created by Manoloon on 12/06/2022.
//

#ifndef PIKUMAENGINE_RIGIDBODYCOMP_H
#define PIKUMAENGINE_RIGIDBODYCOMP_H

#include <SFML/System/Vector2.hpp>

struct RigidBodyComp
        {
    sf::Vector2i velocity;
    explicit RigidBodyComp(const sf::Vector2i &velocity =sf::Vector2i(0.0,0.0)) : velocity(velocity)
    {}
        };
#endif //PIKUMAENGINE_RIGIDBODYCOMP_H

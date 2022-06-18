//
// Created by Manoloon on 12/06/2022.
//

#ifndef PIKUMAENGINE_COMPONENTS_H
#define PIKUMAENGINE_COMPONENTS_H
#include <SFML/System/Vector2.hpp>

struct TransformComp
{
    sf::Vector2i position;
    sf::Vector2i scale;
    double rotation;

    explicit TransformComp(sf::Vector2i position=sf::Vector2i (0,0),sf::Vector2i scale =
    sf::Vector2i (1,1),double rotation = 0.0f)
    {
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }
};

struct RigidBodyComp
{
    sf::Vector2i velocity;

    explicit RigidBodyComp(const sf::Vector2i velocity = sf::Vector2i(0.0, 0.0))
    {
        this->velocity = velocity;
    }
};
#endif //PIKUMAENGINE_COMPONENTS_H

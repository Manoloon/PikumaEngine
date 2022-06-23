//
// Created by Manoloon on 12/06/2022.
//

#ifndef PIKUMAENGINE_COMPONENTS_H
#define PIKUMAENGINE_COMPONENTS_H
#include <SFML/System/Vector2.hpp>

struct TransformComp
{
    sf::Vector2f position;
    sf::Vector2f scale;
    double rotation;

    explicit TransformComp(sf::Vector2f position=sf::Vector2f (0,0),sf::Vector2f scale =
    sf::Vector2f (1,1),double rotation = 0.0f)
    {
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }
};

struct RigidBodyComp
{
    sf::Vector2f velocity;

    explicit RigidBodyComp(const sf::Vector2f velocity = sf::Vector2f(0.0, 0.0))
    {
        this->velocity = velocity;
    }
};

struct SpriteComp
{
    sf::Vector2f scale;
    explicit SpriteComp(sf::Vector2f scale =sf::Vector2f(0,0))
    {
        this->scale = scale;
    }
};
#endif //PIKUMAENGINE_COMPONENTS_H

//
// Created by Manoloon on 24/07/2022.
//

#pragma once

#include "ECS/ECS.h"

class SDebugRender : public System
{
public:
    SDebugRender();

    void Update(sf::RenderWindow &window,sf::RectangleShape& camera,sf::Color color = sf::Color::Green) const;
};

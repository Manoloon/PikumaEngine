//
// Created by Manoloon on 21/08/2022.
//
#pragma once

#include "../ECS/ECS.h"
#include "../Game.h"

class SCamera : public System
{
public:
    SCamera();
    void BeginPlay();
    void Update(sf::RectangleShape& Camera, sf::Time DeltaTime);
};

//
// Created by Manoloon on 21/08/2022.
//
#pragma once

#include "../ECS/ECS.h"
#include "../Game.h"

class CCamera;

class SCamera : public System
{
    CCamera* PlayerCamera = nullptr;
public:
    SCamera();
    void BeginPlay();
    void Update(sf::Time DeltaTime);
    const CCamera* GetCamera() const;
};

//
// Created by Manoloon on 21/08/2022.
//
#pragma once

#include "../ECS/ECS.h"
#include "../Game.h"
#include <optional>

class CCamera;

class SCamera : public System
{ 
    std::optional<Entity> CameraTarget;
public:
    SCamera();
    void BeginPlay(const Registry* registry);
    void Update();
    std::string TargetID = "player";
};

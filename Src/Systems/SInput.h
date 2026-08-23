//
// Created by Manoloon on 31/07/2022.
//
#pragma once

#include "ECS/ECS.h"

class SInput: public System
{
public:
    SInput();
    void Update(float deltaTime);
};

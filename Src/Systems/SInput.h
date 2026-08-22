//
// Created by Manoloon on 31/07/2022.
//
#pragma once

#include "ECS/ECS.h"

class SInput: public System
{
public:
    SInput();
    // consider a per frame pooling of iskeypressed
    // add momentum using acceleration max speed and velocity decay
    void Update(float deltaTime);
};

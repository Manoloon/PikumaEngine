#pragma once
#include "ECS/ECS.h"
#include "Components/Components.h"

class SProjectile : public System
{
public:
    SProjectile();

    void Update(float DeltaTime);
};
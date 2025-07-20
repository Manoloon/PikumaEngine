//
// Created by Manoloon on 09/07/2022.
//

#ifndef PIKUMAENGINE_SANIMATION_H
#define PIKUMAENGINE_SANIMATION_H
#include "Ecs/ECS.h"
#include "Components/Components.h"
class SAnimation: public System
{
public:
    SAnimation();
    void Update();
};
#endif //PIKUMAENGINE_SANIMATION_H
//
// Created by Manoloon on 09/07/2022.
//

#ifndef PIKUMAENGINE_SANIMATION_H
#define PIKUMAENGINE_SANIMATION_H
#include "../ECS/ECS.h"
#include "../Components/Components.h"
class SAnimation: public System
{
public:
    SAnimation()
    {
        RequireComponent<CSprite>();
        RequireComponent<CAnimation>();
    }
    void Update()
    {
        for(auto entity : GetSystemEntities())
        {
            auto& animation = entity.GetComponent<CAnimation>();
            auto& sprite = entity.GetComponent<CSprite>();

            animation.currentFrame++;
            int frame = (animation.currentFrame / animation.frameRateSpeed) % animation.numFrames;
            const int FrameW = sprite.scale.x;
            sprite.spriteRect.left = frame * FrameW;
        }
    }
};
#endif //PIKUMAENGINE_SANIMATION_H

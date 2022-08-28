//
// Created by Manoloon on 09/07/2022.
//

#ifndef PIKUMAENGINE_ANIMATIONSYSTEM_H
#define PIKUMAENGINE_ANIMATIONSYSTEM_H
#include "../ECS/ECS.h"
#include "../Components/Components.h"
class AnimationSystem: public System
{
public:
    AnimationSystem()
    {
        RequireComponent<SpriteComp>();
        RequireComponent<AnimationComp>();
    }
    void Update()
    {
        for(auto entity : GetSystemEntities())
        {
            auto& animation = entity.GetComponent<AnimationComp>();
            auto& sprite = entity.GetComponent<SpriteComp>();

            animation.currentFrame++;
            int frame = (animation.currentFrame / animation.frameRateSpeed) % animation.numFrames;
            const int FrameW = sprite.scale.x;
            sprite.spriteRect.left = frame * FrameW;
        }
    }
};
#endif //PIKUMAENGINE_ANIMATIONSYSTEM_H

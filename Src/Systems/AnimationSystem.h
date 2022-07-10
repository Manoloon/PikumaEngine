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
    void Update(int DeltaTime)
    {
        for(auto entity : GetSystemEntities())
        {
            auto& animation = entity.GetComponent<AnimationComp>();
            auto& sprite = entity.GetComponent<SpriteComp>();

            animation.currentFrame =(DeltaTime - animation.startTime *
                    animation.frameRateSpeed/1000) % animation.numFrames;
            Logger::Warning("startTime = " + std::to_string(animation.startTime));
            Logger::Error("time = " + std::to_string((DeltaTime - animation.startTime *
                                                                         animation
                                                                         .frameRateSpeed/1000)));
            Logger::Warning("Current frame : " + std::to_string(animation.currentFrame));
            sprite.spriteRect = {32 * animation.currentFrame,0,
                    sprite.spriteRect.width,sprite.spriteRect.height};
        }
    }
};
#endif //PIKUMAENGINE_ANIMATIONSYSTEM_H

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
            size_t frame = (animation.currentFrame / animation.frameRateSpeed) % animation
                    .numFrames;
            const auto FrameW = sprite.scale.x;
            const auto FrameH = sprite.scale.y;
            const auto rect = sf::IntRect(frame * FrameW,0,FrameW,FrameH);
            sprite.spriteRect=rect;
        }
    }
};
#endif //PIKUMAENGINE_ANIMATIONSYSTEM_H

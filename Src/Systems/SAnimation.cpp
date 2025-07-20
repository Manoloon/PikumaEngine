#include "SAnimation.h"

SAnimation::SAnimation() 
{
    RequireComponent<CSprite>();
    RequireComponent<CAnimation>();
}

void SAnimation::Update()
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

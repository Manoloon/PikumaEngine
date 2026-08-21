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
        const int FrameW = static_cast<int>(sprite.spriteSize.x);
        auto rect = sprite.spriteRect;
        rect.position.x = frame * FrameW;
        sprite.spriteRect = rect;
    }
}

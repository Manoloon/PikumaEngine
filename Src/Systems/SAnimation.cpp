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
        if(entity.HasTag("Player"))
        {
            auto& keyboard = entity.GetComponent<CKeyboardControlled>();
                   //     // Update sprite direction based on last pressed axis
            if (keyboard.facingDirection.y < 0) sprite.spriteRect.position.y = sprite.spriteRect.size.y * 0; // Up
            else if (keyboard.facingDirection.y > 0) sprite.spriteRect.position.y = sprite.spriteRect.size.y * 2; // Down
            else if (keyboard.facingDirection.x < 0) sprite.spriteRect.position.y = sprite.spriteRect.size.y * 3; // Left
            else if (keyboard.facingDirection.x > 0) sprite.spriteRect.position.y = sprite.spriteRect.size.y * 1; // Right
        }
        animation.currentFrame++;
        int frame = (animation.currentFrame / animation.frameRateSpeed) % animation.numFrames;
        const int FrameW = static_cast<int>(sprite.spriteSize.x);
        auto rect = sprite.spriteRect;
        rect.position.x = frame * FrameW;
        sprite.spriteRect = rect;
    }
}

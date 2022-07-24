//
// Created by Manoloon on 12/06/2022.
//

#ifndef PIKUMAENGINE_COMPONENTS_H
#define PIKUMAENGINE_COMPONENTS_H
#include <SFML/Graphics.hpp>
#include "../Enums/render_Layers.h"
#include <SFML/System/Vector2.hpp>

struct TransformComp
{
    sf::Vector2f position;
    sf::Vector2f scale;
    double rotation;
    /*
     * @position
     * @scale
     * @rotation
     * */
    explicit TransformComp(sf::Vector2f position=sf::Vector2f (0,0),sf::Vector2f scale =
    sf::Vector2f (1,1),double rotation = 0.0f)
    {
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }
};

struct RigidBodyComp
{
    sf::Vector2f velocity;

    explicit RigidBodyComp(const sf::Vector2f velocity = sf::Vector2f(0.0, 0.0))
    {
        this->velocity = velocity;
    }
};

struct SpriteComp
{
    sf::Vector2f scale;
    std::string_view assetId;
    sf::IntRect spriteRect;
    ERenderLayers renderLayer;
    explicit SpriteComp(std::string_view assetId = "",
                        sf::Vector2f newScale =sf::Vector2f(0,0),
                        ERenderLayers newRenderLayers=ERenderLayers::LAYER_PLAYER,
                        sf::Vector2f RectPos=sf::Vector2f(0,0))
    {
        this->assetId = assetId;
        this->scale = newScale;
        this->renderLayer=newRenderLayers;
        this->spriteRect= {static_cast<int>(RectPos.x),
                           static_cast<int>(RectPos.y),
                           static_cast<int>(scale.x),
                           static_cast<int>(scale.y)};
    }
};
struct AnimationComp
{
    int numFrames;
    int currentFrame;
    int frameRateSpeed;
    bool bShouldLoop;
   // int startTime;

    /*
     * @newNumFrames(int) = number of frames
     * @newFrameRateSpeed(int)
    // * @newStartTime(int32)
     * @bLoop
     */
    explicit AnimationComp(int NFrames = 1, int FRateSpeed = 1,
                           bool bLoop = true)
    {
        this->numFrames = NFrames;
        this->currentFrame = 1;
        this->frameRateSpeed = FRateSpeed;
        this->bShouldLoop = bLoop;
      //  this->startTime = StartTime;
    }
};
struct BoxCollisionComp
{
    /*
    * @Size(sf::Vector2f) = Size of the rectangle
    * @offset(sf::Vector2i) = Offset from origin.
    */
    sf::Vector2f size;
    sf::Vector2i offset;
    explicit BoxCollisionComp(sf::Vector2f Size=sf::Vector2f(32.f,32.f),
                              sf::Vector2i Offset=sf::Vector2i(0,0))
                              : size(Size),offset(Offset)
    {}
};
#endif //PIKUMAENGINE_COMPONENTS_H

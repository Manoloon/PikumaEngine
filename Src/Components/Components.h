//
// Created by Manoloon on 12/06/2022.
//

#ifndef PIKUMAENGINE_COMPONENTS_H
#define PIKUMAENGINE_COMPONENTS_H
#include <SFML/Graphics.hpp>
#include "../Enums/ERenderLayers.h"
#include <SFML/System/Vector2.hpp>

struct TransformComp
{
    sf::Vector2f position;
    sf::Vector2f scale;
    float rotation;
    /*
     * @position
     * @scale
     * @rotation
     * */
    explicit TransformComp(sf::Vector2f Position = sf::Vector2f(0.f,0.f),
                           sf::Vector2f Scale = sf::Vector2f (1.0,1.0),
                           double Rotation = 0.0f)
                            : position(Position),scale(Scale),rotation(Rotation){}
};

struct RigidBodyComp
{
    sf::Vector2f velocity;

    explicit RigidBodyComp(const sf::Vector2f Velocity = sf::Vector2f(0.0, 0.0))
                            : velocity(Velocity){}
};

struct SpriteComp
{
    std::string_view assetId;
    sf::Vector2f scale;
    ERenderLayers renderLayer;
    bool bIsUI;
    sf::IntRect spriteRect;
    explicit SpriteComp(std::string_view AssetId = "",
                        sf::Vector2f Scale =sf::Vector2f(1,1),
                        ERenderLayers RenderLayers=ERenderLayers::LAYER_PLAYER,bool isUI=false,
                        sf::Vector2f RectPos=sf::Vector2f(0,0))
                        : assetId(AssetId),
                        scale(Scale), renderLayer(RenderLayers),bIsUI(isUI),
                        spriteRect({static_cast<int>(RectPos.x),
                                    static_cast<int>(RectPos.y),
                                    static_cast<int>(scale.x),
                                    static_cast<int>(scale.y)})
                        {};
};
struct AnimationComp
{
    int numFrames;
    int currentFrame =1;
    int frameRateSpeed;
    bool bShouldLoop;

    /*
     * @newNumFrames(int) = number of frames
     * @newFrameRateSpeed(int)
     * @bLoop
     */
    explicit AnimationComp(int NFrames = 1, int FRateSpeed = 1,
                           bool bLoop = true)
                           : numFrames(NFrames), frameRateSpeed(FRateSpeed),bShouldLoop(bLoop){}
};
struct BoxCollisionComp
{
    /*
    * @Size(sf::Vector2f) = Size of the rectangle
    * @offset(sf::Vector2i) = Offset from origin.
    */
    sf::Vector2f size;
    sf::Vector2f offset;
    explicit BoxCollisionComp(sf::Vector2f Size=sf::Vector2f(32,32),
                              sf::Vector2f Offset=sf::Vector2f(0,0))
                              : size(Size),offset(Offset){}
};

struct KeyboardControlledComp
{
    sf::Vector2f upVelocity;
    sf::Vector2f rightVelocity;
    sf::Vector2f downVelocity;
    sf::Vector2f leftVelocity;
    KeyboardControlledComp(sf::Vector2f UpVelocity=sf::Vector2f(0,0),
                           sf::Vector2f RightVelocity=sf::Vector2f(0,0),
                           sf::Vector2f DownVelocity=sf::Vector2f(0,0),
                           sf::Vector2f LeftVelocity=sf::Vector2f(0,0))
    {
        this->upVelocity=UpVelocity;
        this->rightVelocity=RightVelocity;
        this->downVelocity=DownVelocity;
        this->leftVelocity=LeftVelocity;
    }
};

struct CameraFollowComp
{

};
#endif //PIKUMAENGINE_COMPONENTS_H
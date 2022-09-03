//
// Created by Manoloon on 12/06/2022.
//

#ifndef PIKUMAENGINE_COMPONENTS_H
#define PIKUMAENGINE_COMPONENTS_H
#include <SFML/Graphics.hpp>
#include "../Enums/ERenderLayers.h"
#include <SFML/System/Vector2.hpp>

struct CTransform
{
    sf::Vector2f position;
    sf::Vector2f scale;
    float rotation;
    /**
* \brief Component for actors with presence in the world.
* \param Position sf::Vector2f.
     * \param Scale sf::Vector2f.
     * \param Rotation float.
*/
    explicit CTransform(sf::Vector2f Position = sf::Vector2f(0.f, 0.f),
                        sf::Vector2f Scale = sf::Vector2f (1.0,1.0),
                        double Rotation = 0.0f)
                            : position(Position),scale(Scale),rotation(Rotation){}
};
/**
* \brief Component for actors that have movement.
* \param Velocity sf::Vector2f.
*/
struct CRigidBody
{
    sf::Vector2f velocity;

    explicit CRigidBody(const sf::Vector2f Velocity = sf::Vector2f(0.0, 0.0))
                            : velocity(Velocity){}
};

struct CSprite
{
    std::string_view assetId;
    sf::Vector2f scale;
    ERenderLayers renderLayer;
    bool bIsUI;
    sf::IntRect spriteRect;
    /**
* \brief component for actors with sprites.
* \param AssetID string_view.
 * \param Scale sf::Vector2f.
 * \param RenderLayer ERenderLayers.
 * \param isUI bool
 * \param RectPos sf::Vector2f
*/
    explicit CSprite(std::string_view AssetId = "",
                     sf::Vector2f Scale =sf::Vector2f(1,1),
                     ERenderLayers RenderLayers=ERenderLayers::LAYER_PLAYER, bool isUI=false,
                     sf::Vector2f RectPos=sf::Vector2f(0,0))
                        : assetId(AssetId),
                        scale(Scale), renderLayer(RenderLayers),bIsUI(isUI),
                        spriteRect({static_cast<int>(RectPos.x),
                                    static_cast<int>(RectPos.y),
                                    static_cast<int>(scale.x),
                                    static_cast<int>(scale.y)})
                        {};
};

struct CAnimation
{
    int numFrames;
    int currentFrame =1;
    int frameRateSpeed;
    bool bShouldLoop;
/**
* \brief component for actors with animation.
* \param NFrames int.
 * \param FRateSpeed int.
 * \param ShouldLoop bool.
*/
    explicit CAnimation(int NFrames = 1, int FRateSpeed = 1,
                        bool ShouldLoop = true)
                           : numFrames(NFrames), frameRateSpeed(FRateSpeed),bShouldLoop(ShouldLoop){}
};
struct CBoxCollision
{
    sf::Vector2f size;
    sf::Vector2f offset;
    /**
* \brief component for actors with Collision.
* \param Size sf::Vector2f.
* \param Offset sf::Vector2f.
*/
    explicit CBoxCollision(sf::Vector2f Size=sf::Vector2f(32, 32),
                           sf::Vector2f Offset=sf::Vector2f(0,0))
                              : size(Size),offset(Offset){}
};

struct CKeyboardControlled
{
    sf::Vector2f upVelocity;
    sf::Vector2f rightVelocity;
    sf::Vector2f downVelocity;
    sf::Vector2f leftVelocity;
    /**
* \brief component for actors controlled by keyboard.
* \param UpVelocity sf::Vector2f.
* \param RightVelocity sf::Vector2f.
* \param DownVelocity sf::Vector2f.
* \param LeftVelocity sf::Vector2f.
*/
    CKeyboardControlled(sf::Vector2f UpVelocity=sf::Vector2f(0, 0),
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

struct CCameraFollow
{

};

struct CShootEmitter
{

};
#endif //PIKUMAENGINE_COMPONENTS_H
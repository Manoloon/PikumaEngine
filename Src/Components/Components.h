//
// Created by Manoloon on 12/06/2022.
//
#pragma once

#include "../Enums/EngineEnums.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
/**
* \brief Component for actors with presence in the world.
* \param Position sf::Vector2f.
* \param Scale sf::Vector2f.
* \param Rotation float.
*/
struct CTransform
{
    sf::Vector2f position;
    sf::Vector2f scale;
    sf::Angle rotation;

    explicit CTransform(sf::Vector2f Position = sf::Vector2f(0.f, 0.f),
                        sf::Vector2f Scale = sf::Vector2f(1.0, 1.0),
                        sf::Angle Rotation = sf::degrees(0.f))
        : position(Position), scale(Scale), rotation(Rotation)
    {
    }
};

/**
* \brief Component for actors that have movement.
* \param Velocity sf::Vector2f.
*/
struct CRigidBody
{
    sf::Vector2f velocity;

    explicit CRigidBody(const sf::Vector2f Velocity = {0.0, 0.0}) : velocity(Velocity){}
};
/**
* \brief component for actors with sprites.
* \param AssetID string_view.
* \param Scale sf::Vector2f.
* \param RenderLayer ERenderLayers.
* \param isUI bool
* \param RectPos sf::Vector2f
*/
struct CSprite
{
    std::string_view assetId;
    sf::Vector2f spriteSize;
    ERenderLayers renderLayer;
    bool bIsUI;
    sf::IntRect spriteRect;
    explicit CSprite(std::string_view AssetId = "",
                     sf::Vector2f SpriteSize = {32.f, 32.f},
                     ERenderLayers RenderLayers = ERenderLayers::L_PLAYER,
                     bool isUI = false,
                     sf::Vector2f RectPos = {0.f, 0.f})
        : assetId(AssetId), 
            spriteSize(SpriteSize), 
            renderLayer(RenderLayers), 
            bIsUI(isUI),
          spriteRect({static_cast<int>(RectPos.x), static_cast<int>(RectPos.y)},
                     {static_cast<int>(spriteSize.x), static_cast<int>(spriteSize.y)}) {};
};
/**
* \brief component for actors with animation.
* \param NFrames int.
* \param FRateSpeed int.
* \param ShouldLoop bool.
*/
struct CAnimation
{
    int numFrames;
    int currentFrame = 1;
    int frameRateSpeed;
    bool bShouldLoop;

    explicit CAnimation(int NFrames = 1, int FRateSpeed = 1, bool ShouldLoop = true)
        : numFrames(NFrames), frameRateSpeed(FRateSpeed), bShouldLoop(ShouldLoop)
    {
    }
};
/**
* \brief component for actors with Collision.
* \param Size sf::Vector2f.
* \param Offset sf::Vector2f.
*/
struct CBoxCollision
{
    sf::Vector2f size;
    sf::Vector2f offset;
    explicit CBoxCollision(sf::Vector2f Size = sf::Vector2f(32, 32), sf::Vector2f Offset = sf::Vector2f(0, 0))
        : size(Size), offset(Offset)
    {
    }
};
/**
* \brief component for actors controlled by keyboard.
* \param Up sf::Vector2f.
* \param Right sf::Vector2f.
* \param Down sf::Vector2f.
* \param Left sf::Vector2f.
*/
struct CKeyboardControlled
{
    float acceleration = 500.f; // Units per second squared
    float maxSpeed = 300.f;     // Maximum velocity
    float damping = 0.95f;      // Friction / air resistance per frame

    sf::Vector2f up =    {0.0,-1.0};
    sf::Vector2f right = {1.f, 0.f};
    sf::Vector2f down =  {0.0, 1.0};
    sf::Vector2f left =  {-1.f, 0.f};
    sf::Vector2f inputDirection = {0.f,0.f};
    sf::Vector2f facingDirection = {1.f, 0.f};
    CKeyboardControlled(float Acceleration, float MaxSpeed, float Damping = 0.95f)
    :acceleration(Acceleration),maxSpeed(MaxSpeed),damping(Damping){};
};

struct CCamera
{
    sf::Vector2f position ={0.0f,0.0f};
    sf::Vector2u viewSize = {200,200};
    CCamera(sf::Vector2f Position, sf::Vector2u ViewSize):position(Position),viewSize(ViewSize){};
};

/**
* \brief component for actors that spawn projectiles.
* \param Velocity sf::Vector2f.
* \param LoopFrequency int.
* \param LifeSpan int.
* \param DamagePercent int.
* \param bIsFriendly bool.
* \param lastEmissionTime int. in milliseconds
*/
struct CShootEmitter
{
    sf::Vector2f velocity;
    int loopFrequency;
    int lifeSpan;
    int damagePercentage;
    bool bIsFriendly;
    float lastEmissionTime;

    explicit CShootEmitter(sf::Vector2f Velocity = {0, 0},
                           int LoopFrequency = 1,
                           int LifeSpan = 3,
                           int DamagePercent = 40,
                           bool IsFriendly = false,
                           int LastEmissionTime = 0)
        : velocity(Velocity), loopFrequency(LoopFrequency), lifeSpan(LifeSpan), damagePercentage(DamagePercent),
          bIsFriendly(IsFriendly), lastEmissionTime(LastEmissionTime)
    {
    }
};
/**
* \brief component for actors that handle Health.
* \param Health int. in percentage
*/
struct CHealth
{
    int Health;
    CHealth(int health = 100) : Health(health)
    {
    }
};

/**
*  \brief component that shows a label on screen
*/
struct CTextComponent
{
    sf::Vector2f Position;
    std::string Text;
    std::string_view AssetID;
    sf::Color Color;
    int Size;
    bool IsFixed;
    CTextComponent(sf::Vector2f position,const std::string& text,std::string_view assetID,sf::Color color,int size = 24,bool isFixed = true):
    Position(position),
    Text(text),
    AssetID(assetID),
    Color(color),
    Size(size),
    IsFixed(isFixed){}
};
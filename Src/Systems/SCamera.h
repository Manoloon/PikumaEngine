//
// Created by Manoloon on 21/08/2022.
//
#pragma once

#include "../ECS/ECS.h"
#include "../Game.h"

class SCamera : public System
{
public:
    SCamera()
    {
        RequireComponent<CCameraFollow>();
        RequireComponent<CTransform>();

    }
    void BeginPlay()
    {

    }

    void Update(sf::RectangleShape& Camera, sf::Time DeltaTime)
    {
        for(auto entity : GetSystemEntities())
        {
            auto const& transform = entity.GetComponent<CTransform>();
            float locCameraX;
            float locCameraY;
            float locCamPosX=0;
            float locCamPosY=0;
            if(transform.position.x + (Camera.getSize().x/2) < Game::mapWidth)
            {
                locCamPosX = transform.position.x - (Game::mapWidth /2);
            }
            if(transform.position.y + (Camera.getSize().y/2) < Game::mapHeight)
            {
                locCamPosY = transform.position.y - (Game::mapHeight/2);
            }
            Camera.setPosition(sf::Vector2f{locCamPosX,locCamPosY});
            // TODO : PRoblem!!
            locCameraX = Camera.getPosition().x < 0 ? 0 : Camera.getPosition().x;
            locCameraX = Camera.getPosition().x > Camera.getSize().x ? Camera.getSize().x :
                    Camera.getPosition().x;
            locCameraY = Camera.getPosition().y < 0 ? 0 : Camera.getPosition().y;
            locCameraY = Camera.getPosition().y > Camera.getSize().y ? Camera.getSize().y :
                         Camera.getPosition().y;
            Camera.setPosition(sf::Vector2f{locCameraX,locCameraY});
        }
    }
};

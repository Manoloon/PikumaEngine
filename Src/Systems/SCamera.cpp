#include "SCamera.h"

SCamera::SCamera()
{
    RequireComponent<CCameraFollow>();
    RequireComponent<CTransform>();
}

void SCamera::BeginPlay()
{
}

void SCamera::Update(sf::RectangleShape & Camera, sf::Time DeltaTime)
{
    for(auto entity : GetSystemEntities())
        {
            auto const& transform = entity.GetComponent<CTransform>();
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
        }
}

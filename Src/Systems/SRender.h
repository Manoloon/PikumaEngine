//
// Created by Manoloon on 22/06/2022.
//

#ifndef PIKUMAENGINE_SRENDER_H
#define PIKUMAENGINE_SRENDER_H

#include "../ECS/ECS.h"
#include "../Components/Components.h"
#include <algorithm>
#include "../ECS/AssetStore.h"
#include <SFML/Graphics.hpp>

class SRender : public System
{
public:
    SRender()
    {
        RequireComponent<CTransform>();
        RequireComponent<CSprite>();
    }
    static bool CompareByIndex(const Entity &a,const Entity &b)
    {
        return a.GetComponent<CSprite>().renderLayer <
               b.GetComponent<CSprite>().renderLayer;
    }
  /**
  * \brief Gets the LoginSession object for the provided accountId, and creates one if necessary.
  * \param loginSessionId The AccountId for this login session.
  * \return The login session for that accountId.
  * \remarks If a new login session is created, then LoginSessions.AfterKeyAdded is raised.</remarks>
  */
    void Update(sf::RenderWindow& window,const std::unique_ptr<AssetStore>& assetStore,
                                    const sf::RectangleShape& camera) const
    {
        std::vector<Entity> newEntities = GetSystemEntities();
        std::sort(newEntities.begin(),newEntities.end(), CompareByIndex);
        for(auto entity : newEntities)
        {
            const auto& transformComp = entity.GetComponent<CTransform>();
            const auto& spriteComp = entity.GetComponent<CSprite>();
            // set the source rect for the origin for the sprite
            sf::Sprite sprite;
            sprite.setTexture(*assetStore->GetTexture(spriteComp.assetId));
            sprite.setTextureRect(spriteComp.spriteRect);
            if(!spriteComp.bIsUI)
            {
                sprite.setPosition(transformComp.position - camera.getPosition());
            }
            else
            {
                sprite.setPosition(transformComp.position);
            }
            sprite.setRotation(transformComp.rotation);
            sprite.setScale(transformComp.scale);
            window.draw(sprite);
        }
    }
    /*
    void Draw(sf::RenderWindow& window)
    {
        window.draw(spr)
    }*/
};
#endif //PIKUMAENGINE_SRENDER_H

//
// Created by Manoloon on 22/06/2022.
//

#ifndef PIKUMAENGINE_RENDERSYSTEM_H
#define PIKUMAENGINE_RENDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/Components.h"
#include <algorithm>
#include "../ECS/AssetStore.h"
#include <SFML/Graphics.hpp>

class RenderSystem : public System
{
public:
    RenderSystem()
    {
        RequireComponent<TransformComp>();
        RequireComponent<SpriteComp>();
    }
    static bool CompareByIndex(const Entity &a,const Entity &b)
    {
        return a.GetComponent<SpriteComp>().renderLayer <
               b.GetComponent<SpriteComp>().renderLayer;
    }
    void Update([[maybe_unused]]float DeltaTime,sf::RenderWindow& window,
                                    const std::unique_ptr<AssetStore>& assetStore) const
    {
        std::vector<Entity> newEntities = GetSystemEntities();
        std::sort(newEntities.begin(),newEntities.end(), CompareByIndex);
        for(auto entity : newEntities)
        {
            const auto& transformComp = entity.GetComponent<TransformComp>();
            const auto& spriteComp = entity.GetComponent<SpriteComp>();
            // set the source rect for the origin for the sprite
            sf::Sprite sprite;
            sprite.setTexture(*assetStore->GetTexture(spriteComp.assetId));
            sprite.setTextureRect(spriteComp.spriteRect);
            sprite.setPosition(transformComp.position);
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
#endif //PIKUMAENGINE_RENDERSYSTEM_H

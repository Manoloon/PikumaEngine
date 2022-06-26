//
// Created by Manoloon on 22/06/2022.
//

#ifndef PIKUMAENGINE_RENDERSYSTEM_H
#define PIKUMAENGINE_RENDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/Components.h"
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
    void Update(float DeltaTime,sf::RenderWindow& window,std::unique_ptr<AssetStore>& assetStore)
    {
        for(auto entity : GetSystemEntities())
        {
            const auto transformComp = entity.GetComponent<TransformComp>();
            const auto spriteComp = entity.GetComponent<SpriteComp>();
            // set the source rect for the origin for the sprite
            sf::IntRect srcRect = spriteComp.GetSourceRectangle();
            sf::Sprite sprite;
            sprite.setTexture(*assetStore->GetTexture(spriteComp.assetId));
            sprite.setPosition(transformComp.position);
            sprite.setRotation(transformComp.rotation);
            sprite.setScale(transformComp.scale);
            window.draw(sprite);
        }
    }
};
#endif //PIKUMAENGINE_RENDERSYSTEM_H

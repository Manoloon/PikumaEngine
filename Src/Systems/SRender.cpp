#include "SRender.h"

SRender::SRender()
{
    RequireComponent<CTransform>();
    RequireComponent<CSprite>();
}

bool SRender::CompareByIndex(const Entity &a, const Entity &b) 
{ 
    return a.GetComponent<CSprite>().renderLayer < b.GetComponent<CSprite>().renderLayer;
}

void SRender::Update(sf::RenderWindow &window,
                     AssetStore* assetStore,
                     const sf::RectangleShape &camera) const 
{
    std::vector<Entity> newEntities = GetSystemEntities();
        std::sort(newEntities.begin(),newEntities.end(), CompareByIndex);
        for(auto entity : newEntities)
        {
            const CTransform& transformComp = entity.GetComponent<CTransform>();
            const CSprite& spriteComp = entity.GetComponent<CSprite>();
            // set the source rect for the origin for the sprite
            auto text = assetStore->GetTexture(spriteComp.assetId);
            sf::Sprite sprite(*text);
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

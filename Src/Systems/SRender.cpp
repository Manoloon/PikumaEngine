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

void SRender::Update(sf::RenderWindow &window, AssetStore *assetStore, const CCamera& camera) const
{
    std::vector<Entity> newEntities = GetSystemEntities();
    newEntities.reserve(GetSystemEntities().size());
    std::vector<Entity> rendereableEntities{};
    // TODO : Culling here 
    for(const auto& entity : newEntities)
    {
        if(!entity.HasComponent<CTransform>() || !entity.HasComponent<CSprite>())
        {
            continue;
        }
        if(!bCullActivated)
        {
            rendereableEntities = newEntities;
            break;
        }
        const auto curPos = entity.GetComponent<CTransform>().position;
        const auto curScale = entity.GetComponent<CTransform>().scale;
        const auto curSprite = entity.GetComponent<CSprite>().spriteRect;
        if(CouldBeCull(curPos,curScale,curSprite,camera))
        {
            continue;
        }
        rendereableEntities.emplace_back(entity);
    }
    std::sort(rendereableEntities.begin(), rendereableEntities.end(), CompareByIndex);
    const sf::Vector2f screenCenter = {
                window.getView().getSize().x/2.f,
                window.getView().getSize().y/2.f};
    
    for (auto entity : rendereableEntities)
    {
        CTransform& transformComp = entity.GetComponent<CTransform>();
        const CSprite &spriteComp = entity.GetComponent<CSprite>();

        // set the source rect for the origin for the sprite
        auto texture = assetStore->GetTexture(spriteComp.assetId);
        sf::Sprite sprite(*texture);
        sprite.setTextureRect(spriteComp.spriteRect);
        if (!spriteComp.bIsUI)
        {
            sprite.setOrigin(sf::Vector2f(spriteComp.spriteRect.size)/2.f);
            sprite.setPosition(transformComp.position - camera.position + screenCenter);
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

// TODO : should return a float from 1.0 to 0.0 to handle transparency dither by distance 
bool SRender::CouldBeCull(const sf::Vector2f &EntityPosition,const sf::Vector2f& EntityScale,
                           const sf::IntRect &EntitySprite,
                           const CCamera &Camera) const
{
    return (EntityPosition.x + (EntityScale.x * EntitySprite.size.x) < Camera.position.x ||
            EntityPosition.x > Camera.position.x + Camera.viewSize.x ||
            EntityPosition.y + (EntityScale.y * EntitySprite.size.y) < Camera.position.y ||
            EntityPosition.y > Camera.position.y + Camera.viewSize.y
            );
}
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

void SRender::Update(sf::RenderWindow &window, AssetStore *assetStore, const CCamera &camera)
{
    std::vector<Entity> newEntities = GetSystemEntities();
    std::vector<Entity> rendereableEntities{};
    CameraViewRender(window,camera);
    // 
    for (const auto &entity : newEntities)
    {
        if (!entity.HasComponent<CTransform>() || !entity.HasComponent<CSprite>())
        {
            continue;
        }
        if (!bCullActivated)
        {
            rendereableEntities = newEntities;
            break;
        }
        const auto curPos = entity.GetComponent<CTransform>().position;
        const auto curScale = entity.GetComponent<CTransform>().scale;
        const auto curSprite = entity.GetComponent<CSprite>().spriteRect;
        
        if (CouldBeCull(curPos, curScale, curSprite, camera))
        {
            continue;
        }
        rendereableEntities.emplace_back(entity);
    }
    // render the not culled actors
    std::sort(rendereableEntities.begin(), rendereableEntities.end(), CompareByIndex);
  
    for (auto entity : rendereableEntities)
    {
        CTransform &transformComp = entity.GetComponent<CTransform>();
        const CSprite &spriteComp = entity.GetComponent<CSprite>();

        // set the source rect for the origin for the sprite
        auto texture = assetStore->GetTexture(spriteComp.assetId);
        sf::Sprite sprite(*texture);
        sprite.setTextureRect(spriteComp.spriteRect);
        sprite.setPosition(transformComp.position);
        sprite.setRotation(transformComp.rotation);
        sprite.setScale(transformComp.scale);

        window.draw(sprite);
    }
}

// TODO : should return a float from 1.0 to 0.0 to handle transparency dither by distance
bool SRender::CouldBeCull(const sf::Vector2f &EntityPosition,
                          const sf::Vector2f &EntityScale,
                          const sf::IntRect &EntitySprite,
                          const CCamera &Camera) const
{
    const float halfWidth = Camera.viewSize.x * 0.5f;
    const float halfHeight = Camera.viewSize.y * 0.5f;
    const float left = Camera.position.x - halfWidth;
    const float right = Camera.position.x + halfWidth;
    const float top = Camera.position.y - halfHeight;
    const float bottom = Camera.position.y + halfHeight;

    const float entityRight = EntityPosition.x + EntityScale.x * EntitySprite.size.x;
    const float entityBottom = EntityPosition.y + EntityScale.y * EntitySprite.size.y;

    return entityRight < left || EntityPosition.x > right ||
            entityBottom < top ||EntityPosition.y > bottom;
}

void SRender::CameraViewRender(sf::RenderWindow &window, const CCamera &camera)
{
    sf::View cameraView;
    cameraView.setCenter(camera.position);
    cameraView.setSize(static_cast<sf::Vector2f>(camera.viewSize));
    window.setView(cameraView);
}

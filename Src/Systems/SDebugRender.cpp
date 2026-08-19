#include "SDebugRender.h"

SDebugRender::SDebugRender()
{
    RequireComponent<CTransform>();
    RequireComponent<CBoxCollision>();
}

void SDebugRender::Update(sf::RenderWindow &window,const CCamera& camera, sf::Color color) const
{
    for (auto entity : GetSystemEntities())
    {
        const auto &transform = entity.GetComponent<CTransform>();
        const auto &collider = entity.GetComponent<CBoxCollision>();
        sf::RectangleShape body;
        float LocalWidth = collider.size.x * transform.scale.x;
        float LocalHeight = collider.size.y * transform.scale.y;
        body.setSize({LocalWidth, LocalHeight});
        body.setPosition(transform.position + collider.offset - camera.position);
        body.setOutlineColor(color);
        body.setFillColor(sf::Color::Transparent);
        body.setOutlineThickness(3.f);
        window.draw(body);
    }
}

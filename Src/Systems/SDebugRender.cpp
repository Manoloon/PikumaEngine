#include "SDebugRender.h"

SDebugRender::SDebugRender()
{
    RequireComponent<CTransform>();
    RequireComponent<CBoxCollision>();
}

void SDebugRender::Update(sf::RenderWindow &window, const CCamera &camera, sf::Color color) const
{
    for (auto entity : GetSystemEntities())
    {
        const auto &transform = entity.GetComponent<CTransform>();
        const auto &collider = entity.GetComponent<CBoxCollision>();
        sf::RectangleShape body;

        body.setSize(collider.size);
        body.setScale(transform.scale);
        body.setPosition(transform.position + collider.offset);
        body.setRotation(transform.rotation);
        body.setOutlineColor(color);
        body.setFillColor(sf::Color::Transparent);
        body.setOutlineThickness(3.f);
        window.draw(body);
    }
}

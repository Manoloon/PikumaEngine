#include "SDebugRender.h"

SDebugRender::SDebugRender()
{
    RequireComponent<CTransform>();
    RequireComponent<CBoxCollision>();
}

void SDebugRender::Update(sf::RenderWindow &window, const CCamera &camera, sf::Color color) const
{
    const sf::Vector2f screenCenter = {window.getView().getSize().x / 2.f, window.getView().getSize().y / 2.f};
    for (auto entity : GetSystemEntities())
    {
        const auto &transform = entity.GetComponent<CTransform>();
        const auto &collider = entity.GetComponent<CBoxCollision>();

        sf::RectangleShape body;

        body.setSize(collider.size);
        body.setOrigin({0.f,0.f});
        body.setPosition(transform.position + collider.offset - camera.position + screenCenter);

        body.setOutlineColor(color);
        body.setFillColor(sf::Color::Transparent);
        body.setOutlineThickness(3.f);
        window.draw(body);
    }
}

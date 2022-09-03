//
// Created by Manoloon on 24/07/2022.
//

#ifndef PIKUMAENGINE_SDEBUGRENDER_H
#define PIKUMAENGINE_SDEBUGRENDER_H

#include "../ECS/ECS.h"

class SDebugRender : public System
{
public:
    SDebugRender()
    {
        RequireComponent<CTransform>();
        RequireComponent<CBoxCollision>();
    }

    void Update(sf::RenderWindow &window,sf::RectangleShape& camera,
                                    sf::Color color = sf::Color::Green) const
    {
        for (auto entity: GetSystemEntities()) {
            const auto &transform = entity.GetComponent<CTransform>();
            const auto &collider = entity.GetComponent<CBoxCollision>();
            sf::RectangleShape body;
            float LocalWidth = collider.size.x * transform.scale.x;
            float LocalHeight = collider.size.y * transform.scale.y;
            body.setSize({LocalWidth,LocalHeight});
            body.setPosition(transform.position + collider.offset - camera.getPosition());
            body.setOutlineColor(color);
            body.setFillColor(sf::Color::Transparent);
            body.setOutlineThickness(3.f);
            window.draw(body);
        }
    }
};
#endif //PIKUMAENGINE_SDEBUGRENDER_H

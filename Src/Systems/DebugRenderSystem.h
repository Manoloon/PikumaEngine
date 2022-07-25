//
// Created by Manoloon on 24/07/2022.
//

#ifndef PIKUMAENGINE_DEBUGRENDERSYSTEM_H
#define PIKUMAENGINE_DEBUGRENDERSYSTEM_H

#include "../ECS/ECS.h"

class DebugRenderSystem : public System
{
public:
    DebugRenderSystem()
    {
        RequireComponent<TransformComp>();
        RequireComponent<BoxCollisionComp>();
    }

    void Update(sf::RenderWindow &window, sf::Color color = sf::Color::Green) const
    {
        for (auto entity: GetSystemEntities()) {
            const auto &transform = entity.GetComponent<TransformComp>();
            const auto &collider = entity.GetComponent<BoxCollisionComp>();
            sf::RectangleShape body;
            body.setSize(collider.size);
            body.setPosition(transform.position);
            body.setOutlineColor(color);
            body.setFillColor(sf::Color::Transparent);
            body.setOutlineThickness(3.f);
            window.draw(body);
        }
    }
};
#endif //PIKUMAENGINE_DEBUGRENDERSYSTEM_H

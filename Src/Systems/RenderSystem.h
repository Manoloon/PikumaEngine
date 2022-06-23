//
// Created by Manoloon on 22/06/2022.
//

#ifndef PIKUMAENGINE_RENDERSYSTEM_H
#define PIKUMAENGINE_RENDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/Components.h"
#include <SFML/Graphics.hpp>

class RenderSystem : public System
{
public:
    RenderSystem()
    {
        RequireComponent<TransformComp>();
        RequireComponent<SpriteComp>();
    }
    void Update(float DeltaTime,sf::RenderWindow& window)
    {
        for(auto entity : GetSystemEntities())
        {
            const auto transform = entity.GetComponent<TransformComp>();
            const auto sprite = entity.GetComponent<SpriteComp>();
            sf::RectangleShape rectangle;
            rectangle.setFillColor(sf::Color(255, 255, 255,255));
            rectangle.setOrigin(rectangle.getSize().x/2,rectangle.getSize().y/2);
            rectangle.setOutlineColor(sf::Color(3,63,81,255));
            rectangle.setOutlineThickness(2.f);
            rectangle.setSize(sprite.scale);
            rectangle.setPosition(transform.position);
            window.clear(sf::Color(18,33,43));
            window.draw(rectangle);
            window.display();
        }

    }
};
#endif //PIKUMAENGINE_RENDERSYSTEM_H

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
            rectangle.setSize(sprite.scale);
            rectangle.setPosition(transform.position);
            window.draw(rectangle);
        }

    }
};
#endif //PIKUMAENGINE_RENDERSYSTEM_H

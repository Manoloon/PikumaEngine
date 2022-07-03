//
// Created by Manoloon on 12/06/2022.
//

#ifndef PIKUMAENGINE_COMPONENTS_H
#define PIKUMAENGINE_COMPONENTS_H
#include <SFML/Graphics.hpp>
#include "../Enums/render_Layers.h"
#include <SFML/System/Vector2.hpp>

struct TransformComp
{
    sf::Vector2f position;
    sf::Vector2f scale;
    double rotation;
    /*
     * @position
     * @scale
     * @rotation
     * */
    explicit TransformComp(sf::Vector2f position=sf::Vector2f (0,0),sf::Vector2f scale =
    sf::Vector2f (1,1),double rotation = 0.0f)
    {
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }
};

struct RigidBodyComp
{
    sf::Vector2f velocity;

    explicit RigidBodyComp(const sf::Vector2f velocity = sf::Vector2f(0.0, 0.0))
    {
        this->velocity = velocity;
    }
};

struct SpriteComp
{
    sf::Vector2f scale;
    std::string_view assetId;
    sf::IntRect spriteRect;
    ERenderLayers renderLayer;
    explicit SpriteComp(std::string_view assetId = "",
                        sf::Vector2f newScale =sf::Vector2f(0,0),
                        ERenderLayers newRenderLayers=ERenderLayers::LAYER_PLAYER,
                        sf::Vector2f RectPos=sf::Vector2f(0,0))
    {
        this->assetId = assetId;
        this->scale = newScale;
        this->renderLayer=newRenderLayers;
        this->spriteRect= {static_cast<int>(RectPos.x),
                           static_cast<int>(RectPos.y),
                           static_cast<int>(scale.x),
                           static_cast<int>(scale.y)};
    }
public:
    [[nodiscard]] sf::IntRect GetSourceRectangle()const{return spriteRect;}
    int GetLayerIndex() const {return renderLayer;}
};
#endif //PIKUMAENGINE_COMPONENTS_H

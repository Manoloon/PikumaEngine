//
// Created by Manoloon on 26/05/2022.
//

#ifndef PIKUMAENGINE_TRANSFORMCOMP_H
#define PIKUMAENGINE_TRANSFORMCOMP_H
#include <SFML/Graphics.hpp>
struct TransformComp
        {
            sf::Vector2i position;
            sf::Vector2i scale;
            double rotation;

            explicit TransformComp(sf::Vector2i position=sf::Vector2i (0,0),sf::Vector2i scale =
                    sf::Vector2i (1,1),double rotation = 0.0f)
            {
                this->position = position;
                this->scale = scale;
                this->rotation = rotation;
            }
        };
#endif //PIKUMAENGINE_TRANSFORMCOMP_H

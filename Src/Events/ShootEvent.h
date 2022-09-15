//
// Created by Manoloon on 12/09/2022.
//

#ifndef PIKUMAENGINE_SHOOTEVENT_H
#define PIKUMAENGINE_SHOOTEVENT_H
#include "../ECS/ECS.h"
#include "Event.h"

class ShootEvent : public Event
{
public:
    sf::Keyboard::Key keyCode;
    explicit ShootEvent(sf::Keyboard::Key KeyCode):keyCode(KeyCode){}
};
#endif //PIKUMAENGINE_SHOOTEVENT_H

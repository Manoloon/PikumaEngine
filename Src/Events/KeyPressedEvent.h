//
// Created by Manoloon on 31/07/2022.
//

#ifndef PIKUMAENGINE_KEYPRESSEDEVENT_H
#define PIKUMAENGINE_KEYPRESSEDEVENT_H

#include "Event.h"

class KeyPressedEvent : public Event
        {
public:
    sf::Keyboard::Key keySymbol;
    explicit KeyPressedEvent(sf::Keyboard::Key keySymbol)
                            : keySymbol(keySymbol){}
        };
#endif //PIKUMAENGINE_KEYPRESSEDEVENT_H

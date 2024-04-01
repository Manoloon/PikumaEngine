//
// Created by Manoloon on 31/07/2022.
//
#pragma once

#include "Event.h"

class KeyPressedEvent : public Event
        {
public:
    sf::Keyboard::Key KeySymbol;
    explicit KeyPressedEvent(sf::Keyboard::Key keySymbol)
                            : KeySymbol(keySymbol){}
        };

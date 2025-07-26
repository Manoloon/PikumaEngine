//
// Created by Manoloon on 31/07/2022.
//
#pragma once

#include "Event.h"

class KeyPressedEvent : public Event
{
public:
        sf::Keyboard::Key KeySymbol;
        explicit KeyPressedEvent(sf::Keyboard::Key keySymbol): KeySymbol(keySymbol){}
};
// TODO : implement the key released event
class KeyReleasedEvent : public Event
{
public:
        sf::Keyboard::Key KeySymbol;
        explicit KeyReleasedEvent(sf::Keyboard::Key keySymbol): KeySymbol(keySymbol){}
};
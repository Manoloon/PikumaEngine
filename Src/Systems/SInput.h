//
// Created by Manoloon on 31/07/2022.
//
#pragma once

#include "ECS/ECS.h"
#include "ECS/EventBus.h"
#include "Events/KeyPressedEvent.h"

class SInput: public System
{
public:
    SInput();

    void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus);

    void onKeyPressed(KeyPressedEvent& event);
    // consider a per frame pooling of iskeypressed
    // add momentum using acceleration max speed and velocity decay
    void Update(float deltaTime);
};

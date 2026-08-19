#pragma once

#include "imgui-SFML.h"
#include "ECS/ECS.h"
#include "imgui.h"

class SRenderDebugGUI : public System
{
public:
    void Update(sf::RenderWindow& window, sf::Time DeltaTime,std::unique_ptr<Registry>& Registry,const CCamera& cameraActor);
};
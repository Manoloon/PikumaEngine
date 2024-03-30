#pragma once

#include "../ECS/ECS.h"
#include "imgui-SFML.h"
#include "imgui.h"

class SRenderDebugGUI : public System
{
    public:
        void Update(sf::RenderWindow& window, sf::Time DeltaTime)
        {
            ImGui::SFML::Update(window,DeltaTime);
            if(ImGui::Begin("Create Enemies"))
            {
                ImGui::Text("new enemy");
            }
            ImGui::End();
            //ImGui::ShowDemoWindow();
            ImGui::SFML::Render(window);
        }
};
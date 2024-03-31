#pragma once

#include "imgui-SFML.h"
#include "imgui.h"
#include <ECS/ECS.h>

class SRenderDebugGUI : public System
{
    public:
        void Update(sf::RenderWindow& window, sf::Time DeltaTime,std::unique_ptr<Registry>& Registry)
        {
            ImGui::SFML::Update(window,DeltaTime);
            static int NewXPos;
            static int NewYPos;
            if(ImGui::Begin("Create Enemies"))
            {
                ImGui::Text("new enemy");
                ImGui::InputInt("New x Position:",&NewXPos);
                ImGui::InputInt("New y Position:",&NewYPos);
                if(ImGui::Button("Create"))
                {
                    Entity Tank = Registry->CreateEntity();
                    Tank.Group("Enemies");
                    Tank.AddComponent<CTransform>(sf::Vector2f(NewXPos,NewYPos), sf::Vector2f(2.0, 2.0), 0.0);
                    Tank.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
                    Tank.AddComponent<CShootEmitter>(sf::Vector2f(50,10),20000,20000,false);
                    Tank.AddComponent<CSprite>("tank-image", sf::Vector2f(32.f, 32.f), ERenderLayers::LAYER_ENEMIES);
                    Tank.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));
                }
            }
            ImGui::End();
            //ImGui::ShowDemoWindow();
            ImGui::SFML::Render(window);
        }
};
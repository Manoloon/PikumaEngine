#include "SRenderDebugGUI.h"
#include "GameGlobals.h"
#include "ECS/ECS.h"

void SRenderDebugGUI::Update(sf::RenderWindow &window, sf::Time DeltaTime,
                             std::unique_ptr<Registry> &Registry,
                             sf::RectangleShape &cameraActor) 
{
    ImGui::SFML::Update(window,DeltaTime);
            static int NewXPos;
            static int NewYPos;
            static float NewScale;
            static float NewRotation;
            static float NewXSpeed;
            static float NewYSpeed;

            if(ImGui::Begin("Create Enemies"))
            {
                ImGui::Text("new enemy");
                ImGui::InputInt("Position X :",&NewXPos);
                ImGui::InputInt("Position Y :",&NewYPos);
                ImGui::SliderFloat("Scale :", &NewScale,0.2,4);
                ImGui::SliderAngle("Rotation (deg):", &NewRotation,0,360);
                ImGui::Spacing();
                ImGui::SliderFloat("Velocity X:",&NewXSpeed,0,500);
                ImGui::SliderFloat("Velocity Y:",&NewYSpeed,0,500);
                ImGui::Spacing();
                if(ImGui::Button("Create"))
                {
                    Entity Tank = Registry->CreateEntity();
                    Tank.Group("Enemies");
                    Tank.AddComponent<CTransform>(sf::Vector2f(NewXPos,NewYPos), sf::Vector2f(NewScale, NewScale),NewRotation);
                    Tank.AddComponent<CRigidBody>(sf::Vector2f(NewXSpeed, NewYSpeed));
                    Tank.AddComponent<CShootEmitter>(sf::Vector2f(50,10),20000,20000,false);
                    Tank.AddComponent<CSprite>("tank-image", sf::Vector2f(32.f * NewScale, 32.f * NewScale), ERenderLayers::L_ENEMIES);
                    Tank.AddComponent<CBoxCollision>(sf::Vector2f(32.f * NewScale, 32.f * NewScale));
                }
            }
            ImGui::End();
            ImGuiWindowFlags windowFlags =  ImGuiWindowFlags_NoDecoration | 
                                            ImGuiWindowFlags_AlwaysAutoResize |
                                            ImGuiWindowFlags_NoNav;
            ImGui::SetNextWindowPos(ImVec2(10,10),ImGuiCond_Always, ImVec2(0,0));
            ImGui::SetNextWindowBgAlpha(0.9f);
            if(ImGui::Begin("Map Coordinates :", NULL, windowFlags))
            {
                ImGui::Text(
                        "Map Coordinates (x= %.1f, y= %.1f)",
                        ImGui::GetIO().MousePos.x + cameraActor.getPosition().x,
                        ImGui::GetIO().MousePos.y + cameraActor.getPosition().y);
                        ImGui::Spacing();
                        ImGui::Text("FPS > %.1f",CurrentGameFPS);
            }
            ImGui::End();
            ImGui::SFML::Render(window);
}

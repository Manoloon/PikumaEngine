#include <iostream>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <sol/sol.hpp>
#include <imgui/imgui-SFML.h>

int main()
{
   glm::vec2 speed = glm::vec2(10.0f,10.f);
   //sol::state lua;
   //lua.open_libraries(sol::lib::base);
   sf::RenderWindow window(sf::VideoMode(800,600),"pikuma engine");
   sf::CircleShape shape(200.f,100);
   shape.setFillColor(sf::Color(200,77,4));
   shape.setPosition(200,200);
   //ImGui::SFML::Init(window);
   sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
           // ImGui::SFML::ProcessEvent(event);
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
           // ImGui::SFML::Update(window,clock.restart());
            window.clear(sf::Color(18,33,43));
            window.draw(shape);
          //  ImGui::SFML::Render(window);
            window.display();
        }
    }
    //ImGui::SFML::Shutdown();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

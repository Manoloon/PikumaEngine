cmake_minimum_required(VERSION 3.22)
project(PikumaEngine)
set(CMAKE_CXX_STANDARD 17)
SET(SFML_STATIC_LIBRARIES TRUE)
add_executable(PikumaEngine main.cpp Src/Game.cpp Src/Game.h Src/Logger.h Src/Systems/SMovement.h
        Src/ECS/ECS.h Src/ECS/ECS.cpp Src/Components/Components.h Src/Systems/SRender.h
                                                        Src/ECS/AssetStore.cpp Src/ECS/AssetStore.h Src/Enums/ERenderLayers.h Src/Systems/SAnimation.h Src/Systems/SCollision.h Src/Systems/SDebugRender.h Src/ECS/EventBus.h Src/Events/CollisionEvent.h Src/Events/Event.h Src/Systems/SDamage.h Src/Systems/SInput.h Src/Events/KeyPressedEvent.h Src/Systems/SCamera.h Src/Systems/SProjectileEmitter.h Src/Events/ShootEvent.h)
include_directories (Includes/)
#Lua
find_library(LUA lua53 libraries)
#SFML
find_package(SFML COMPONENTS system window graphics audio)
target_link_libraries(PikumaEngine sfml-graphics sfml-window sfml-system sfml-audio ${LUA})
#ImGui-SFML::ImGui-SFML

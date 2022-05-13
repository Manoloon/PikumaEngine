cmake_minimum_required(VERSION 3.22)
project(PikumaEngine)
set(CMAKE_CXX_STANDARD 17)
SET(SFML_STATIC_LIBRARIES TRUE)
add_executable(PikumaEngine main.cpp Game.cpp Game.h)
include_directories (Includes/)
#Lua
find_library(LUA lua53 libraries)
#SFML
find_package(SFML COMPONENTS system window graphics audio)
target_link_libraries(PikumaEngine sfml-graphics sfml-window sfml-system ${LUA})
#ImGui-SFML::ImGui-SFML

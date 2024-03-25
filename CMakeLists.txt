cmake_minimum_required(VERSION 3.25.0)
project(PikumaEngine VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(SFML_STATIC_LIBRARIES TRUE)
include_directories(${CMAKE_SOURCE_DIR}/Includes)

add_executable(PikumaEngine main.cpp)

# Add all source files from the 'Src' directory
file(GLOB_RECURSE SRC_FILES "Src/*.cpp")
target_sources(PikumaEngine PRIVATE ${SRC_FILES})

#IMGUI
 
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/Includes/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui-SFML.cpp)

option(IMGUI_SFML_FIND_SFML ON)
option(IMGUI_SFML_IMGUI_DEMO ON)

include_directories(${IMGUI_DIR})
target_link_libraries(PikumaEngine PRIVATE ImGui-SFML)

#SFML
find_package(SFML COMPONENTS system window graphics audio REQUIRED)
target_link_libraries(PikumaEngine PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# Find and link Lua library
find_library(LUA lua53 REQUIRED)

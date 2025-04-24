cmake_minimum_required(VERSION 3.25.0)
project(PikumaEngine VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(SFML_STATIC_LIBRARIES TRUE)
include_directories(${CMAKE_SOURCE_DIR}/Src)

add_subdirectory(Externals)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow)
endif()

add_executable(PikumaEngine main.cpp
    Src/Game.cpp
    Src/ECS/AssetStore.cpp
    Src/ECS/ECS.cpp
    )
target_link_libraries(PikumaEngine PRIVATE ImGui-SFML)
target_link_libraries(PikumaEngine PRIVATE sfml-graphics sfml-window sfml-system sfml-audio ImGui-SFML::ImGui-SFML)


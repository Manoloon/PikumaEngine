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

#SFML
find_package(SFML COMPONENTS system window graphics audio REQUIRED)
target_link_libraries(PikumaEngine PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# Find and link Lua library
find_library(LUA lua53 REQUIRED)
target_link_libraries(PikumaEngine PRIVATE ${LUA})
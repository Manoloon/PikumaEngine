cmake_minimum_required(VERSION 3.22)
project(PikumaEngine)

set(CMAKE_CXX_STANDARD 20)
SET(SFML_STATIC_LIBRARIES TRUE)
add_executable(PikumaEngine main.cpp)
find_package(SFML COMPONENTS system window graphics audio)
target_link_libraries(PikumaEngine sfml-system sfml-window sfml-graphics sfml-audio -static)


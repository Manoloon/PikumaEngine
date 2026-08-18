cmake_minimum_required(VERSION 3.25.0)
project(PikumaEngine VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(SFML_STATIC_LIBRARIES TRUE)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow)
endif()

add_subdirectory(Externals)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Src)
set(SOURCES
    ${SRC_DIR}/Game.cpp
    ${SRC_DIR}/Logger.cpp
    ${SRC_DIR}/GameGlobals.cpp
    ${SRC_DIR}/ECS/ECS.cpp
    ${SRC_DIR}/ECS/AssetStore.cpp
    ${SRC_DIR}/Systems/SAnimation.cpp
    ${SRC_DIR}/Systems/SCamera.cpp
    ${SRC_DIR}/Systems/SCollision.cpp
    ${SRC_DIR}/Systems/SDamage.cpp
    ${SRC_DIR}/Systems/SInput.cpp
    ${SRC_DIR}/Systems/SDebugRender.cpp
    ${SRC_DIR}/Systems/SMovement.cpp
    ${SRC_DIR}/Systems/SProjectileEmitter.cpp
    ${SRC_DIR}/Systems/SRender.cpp
    ${SRC_DIR}/Systems/SRenderDebugGUI.cpp
    )

add_executable(PikumaEngine main.cpp ${SOURCES}
    Src/LevelLoader.cpp)
target_include_directories(PikumaEngine PRIVATE ${SRC_DIR})

# Asset directory copy to build folder
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")

file(GLOB_RECURSE ASSET_FILES
    CONFIGURE_DEPENDS
    "${ASSETS_DIR}/*"
)

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ASSETS_DIR}"
        "${CMAKE_BINARY_DIR}/assets"
)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

target_link_libraries(PikumaEngine PRIVATE
                        ImGui-SFML::ImGui-SFML
                        SFML::Graphics
                        SFML::Window 
                        SFML::System 
                        SFML::Audio 
                        )

get_filename_component(MINGW64_ROOT
    "${CMAKE_CXX_COMPILER}"
    DIRECTORY
)

get_filename_component(MINGW64_ROOT
    "${MINGW64_ROOT}"
    DIRECTORY
)
set(LUA_ROOT "${MINGW64_ROOT}/include/lua5.4")

target_include_directories(PikumaEngine PRIVATE
    "${MINGW64_ROOT}/include"
    "${LUA_ROOT}"
)

target_link_libraries(PikumaEngine PRIVATE
    "${MINGW64_ROOT}/lib/liblua5.4.dll.a"
)

# target_include_directories(PikumaEngine PRIVATE
#     "C:/msys64/mingw64/include"
#     "C:/msys64/mingw64/include/lua5.4"
# )

# target_link_libraries(PikumaEngine PRIVATE
#     "C:/msys64/mingw64/lib/liblua5.4.dll.a"
# )

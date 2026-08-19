include(FetchContent)

Set(FETCHCONTENT_QUIET FALSE)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.91.9b
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(ImGui)

set(IMGUI_DIR "${imgui_SOURCE_DIR}")
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)

FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG master
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(ImGui-SFML)

# FetchContent_Declare(ImPlot
#     GIT_REPOSITORY https://github.com/epezent/implot
#     GIT_TAG v0.16
#     GIT_PROGRESS TRUE)
# FetchContent_MakeAvailable(ImPlot)

# add_library(ImPlot
#     "${implot_SOURCE_DIR}/implot.cpp"
#     "${implot_SOURCE_DIR}/implot_items.cpp"
#     "${imgui_SOURCE_DIR}/imgui.cpp"
#     "${imgui_SOURCE_DIR}/imgui_draw.cpp"
#     "${imgui_SOURCE_DIR}/imgui_tables.cpp"
#     "${imgui_SOURCE_DIR}/imgui_widgets.cpp")
# add_library(ImPlot::ImPlot ALIAS ImPlot)
# target_include_directories(ImPlot PUBLIC "${implot_SOURCE_DIR}" "${imgui_SOURCE_DIR}")
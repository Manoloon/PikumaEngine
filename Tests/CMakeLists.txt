add_executable(ECS_tests
    ECS_unitTests.cpp
)

target_link_libraries(ECS_tests
    PRIVATE
    PikumaEngineCore
    Catch2::Catch2WithMain
)

catch_discover_tests(ECS_tests)
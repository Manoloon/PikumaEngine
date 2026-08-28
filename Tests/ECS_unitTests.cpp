#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "../Src/Components/Components.h"
#include "../Src/ECS/ECS.h"

std::unique_ptr<Registry> registry = std::make_unique<Registry>();

TEST_CASE("01- Entity creation", "[Entity]")
{
    REQUIRE(registry != nullptr);
}
TEST_CASE("02- Entity Tag", "[Entity]")
{
    auto entity = registry->CreateEntity();
    entity.Tag("player");
    REQUIRE(entity.HasTag("player"));
    REQUIRE(registry->GetEntityByTag("player") == entity);
}
TEST_CASE("03- Entity Group", "[Entity]")
{
    auto entity = registry->CreateEntity();
    entity.Group("entities");
    REQUIRE(entity.BelongToGroup("entities"));
    auto entities = registry->GetEntitiesByGroup("entities");
    REQUIRE_FALSE(entities.empty());
}
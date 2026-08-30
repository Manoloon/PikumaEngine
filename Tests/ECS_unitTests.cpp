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
    // adding a second player
    auto entityA = registry->CreateEntity();
    REQUIRE_THROWS(entityA.Tag("player"));

    auto result = registry->GetEntityByTag("player");
    REQUIRE(result.has_value());
    REQUIRE(result == entity);
}

TEST_CASE("03- Entity Group", "[Entity]")
{
    auto entity = registry->CreateEntity();
    entity.Group("entities");
    REQUIRE(entity.BelongToGroup("entities"));
    auto entities = registry->GetEntitiesByGroup("entities");
    REQUIRE_FALSE(entities.empty());
}
TEST_CASE("04-Entity Operators","[Entity]")
{
    // adding a second player
    auto entityA = registry->CreateEntity();
    
    auto entityB = registry->CreateEntity();
    entityB.Tag("enemy");
    REQUIRE(entityA != entityB);
    REQUIRE(entityA < entityB);
    REQUIRE(entityB > entityA);
    auto other = registry->GetEntityByTag("enemy");
    REQUIRE(other.has_value());
    REQUIRE(entityB.GetId() == other->GetId());
}
TEST_CASE("05-Add Component to Entity", "[Entity]")
{
    auto entity = registry->CreateEntity();
    entity.Group("enemy");
    const sf::Vector2f pos = {100,200};
    const sf::Vector2f scale = {2.0,2.0};
    const sf::Angle rot = sf::degrees(90.f);
    entity.AddComponent<CTransform>(pos,scale,rot);
    REQUIRE(entity.HasComponent<CTransform>());
    auto comp = registry->GetComponent<CTransform>(entity);
    REQUIRE(comp.position == pos);
    REQUIRE(comp.scale == scale);
    REQUIRE(comp.rotation == rot);
}
TEST_CASE("07-Remove component from entity", "[Entity]")
{
auto entities = registry->GetEntitiesByGroup("enemy");

    REQUIRE_FALSE(entities.empty());

    for (auto& entity : entities)
    {
        if (entity.HasComponent<CTransform>())
        {
            REQUIRE_NOTHROW(entity.RemoveComponent<CTransform>());
            REQUIRE_FALSE(entity.HasComponent<CTransform>());
            return;
        }
    }

    FAIL("No enemy with CTransform was found");
}
TEST_CASE("08-Destroy player Entity","[Entity]")
{
    auto entity = registry->GetEntityByTag("player");
    REQUIRE(entity.has_value());
    entity->Destroy();
    registry->Update();
    entity = registry->GetEntityByTag("player");
    REQUIRE_FALSE(entity);
    REQUIRE_FALSE(entity.has_value());
}

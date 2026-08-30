#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "../Src/Components/Components.h"
#include "Systems/SMovement.h"
#include "../Src/ECS/ECS.h"

struct RegistryFixture
{
    std::unique_ptr<Registry> registry = std::make_unique<Registry>();
};

TEST_CASE_METHOD(RegistryFixture,"Entity creation", "[Entity]")
{
    REQUIRE(registry != nullptr);
    auto entity = registry->CreateEntity();
    int id = entity.GetId();
    REQUIRE(id == 0);
}
TEST_CASE_METHOD(RegistryFixture,"Entities received different ID", "[Entity]")
{
    auto entityA = registry->CreateEntity();
    auto entityB = registry->CreateEntity();
    auto entityC = registry->CreateEntity();

    REQUIRE(entityA != entityB);
    REQUIRE(entityB != entityC);
    REQUIRE(entityC != entityA);
}
TEST_CASE_METHOD(RegistryFixture,"Entity Tag", "[Tag]")
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
TEST_CASE_METHOD(RegistryFixture,"Unknown tag returns no entity", "[Tag]")
{
    auto result = registry->GetEntityByTag("player");
    REQUIRE_FALSE(result.has_value());
}
TEST_CASE_METHOD(RegistryFixture,"Entity Group", "[Entity]")
{
    auto entity = registry->CreateEntity();
    entity.Group("entities");
    REQUIRE(entity.BelongToGroup("entities"));
    REQUIRE(registry->EntityBelongToGroup(entity,"entities"));
    auto entities = registry->GetEntitiesByGroup("entities");
    REQUIRE_FALSE(entities.empty());
    registry->RemoveEntityGroup(entity);
    REQUIRE_FALSE(registry->EntityBelongToGroup(entity,"entities"));
    REQUIRE_FALSE(entity.BelongToGroup("entities"));
    entities = registry->GetEntitiesByGroup("entities");
    REQUIRE(entities.empty());
}
TEST_CASE_METHOD(RegistryFixture,"Entity Operators","[Entity]")
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

TEST_CASE_METHOD(RegistryFixture,"Add Component to Entity", "[Entity]")
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

TEST_CASE_METHOD(RegistryFixture,"Remove component from entity", "[Entity]")
{
    auto entity = registry->CreateEntity();
    entity.Group("enemy");
    const sf::Vector2f pos = {100,200};
    const sf::Vector2f scale = {2.0,2.0};
    const sf::Angle rot = sf::degrees(90.f);
    entity.AddComponent<CTransform>(pos,scale,rot);
    REQUIRE(entity.HasComponent<CTransform>());

    auto entities = registry->GetEntitiesByGroup("enemy");
    REQUIRE_FALSE(entities.empty());

    for (auto& e : entities)
    {
        if (e.HasComponent<CTransform>())
        {
            REQUIRE_NOTHROW(e.RemoveComponent<CTransform>());
            REQUIRE_FALSE(e.HasComponent<CTransform>());
            return;
        }
    }
    FAIL("No enemy with CTransform was found");
}
TEST_CASE_METHOD(RegistryFixture,"Destroy player Entity","[Entity]")
{
    auto entity = registry->CreateEntity();
    entity.Tag("player");

    auto entityResult = registry->GetEntityByTag("player");
    REQUIRE(entityResult.has_value());
    
    entityResult->Destroy();
    registry->Update();
    entityResult = registry->GetEntityByTag("player");
    REQUIRE_FALSE(entityResult);
    REQUIRE_FALSE(entityResult.has_value());
}
// TEST_CASE("09-Add and remove Entity To system","[Entity]")
// {
//     auto system = registry->GetSystem<SMovement>();

// }
// /// TEST SYSTEM
// TEST_CASE("01-Test Systems - Add, remove , Has? , Get","[System]")
// {

// }
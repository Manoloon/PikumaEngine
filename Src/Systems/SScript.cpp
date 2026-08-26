#include "SScript.h"
#include <sol/sol.hpp>

void SScript::CreateBindings(sol::state &lua)
{
    lua.new_usertype<Entity>("entity",
                            "get_id", &Entity::GetId,
                            "destroy", &Entity::Destroy,
                            "has_tag", &Entity::HasTag,
                            "belong_to_group", &Entity::BelongToGroup);
    lua.set_function("get_position", GetEntityPosition);
    lua.set_function("set_position", SetEntityPosition);
}

SScript::SScript()
{
    RequireComponent<CScript>();
}

void SScript::Update()
{
    for(const auto& entity : GetSystemEntities())
    {
        auto& scriptComp = entity.GetComponent<CScript>();
        scriptComp.function();
    }
}

std::tuple<double, double> GetEntityPosition(Entity entity)
{
    if(!entity.HasComponent<CTransform>())
    {
        Logger::Error("SScript::GetEntityPosition : entity has NOT CTransform");
        return {0.0,0.0};
    }
    auto& transform = entity.GetComponent<CTransform>();
    return {transform.position.x,transform.position.y};
}

void SetEntityPosition(Entity entity, double x, double y)
{
    if(!entity.HasComponent<CTransform>())
    {
        Logger::Error("SScript::SetEntityPosition : entity has NOT CTransform");
        return;
    }
    auto& transform = entity.GetComponent<CTransform>();
        transform.position.x = x;
        transform.position.y = y;
}

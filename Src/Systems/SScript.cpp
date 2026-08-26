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
    lua.set_function("get_velocity", GetEntityVelocity);
    lua.set_function("set_velocity", SetEntityVelocity);
    lua.set_function("get_rotation", GetEntityRotation);
    lua.set_function("set_rotation", SetEntityRotation);
    lua.set_function("get_projectile_velocity", GetProjectileVelocity);
    lua.set_function("set_projectile_velocity", SetProjectileVelocity);
}

SScript::SScript()
{
    RequireComponent<CScript>();
}

void SScript::Update(float DeltaTime,float EllapsedTime)
{
    for(auto entity : GetSystemEntities())
    {
        auto& scriptComp = entity.GetComponent<CScript>();
        sol::protected_function_result result =
            scriptComp.function(entity, DeltaTime, EllapsedTime);

        if (!result.valid())
        {
            sol::error error = result;
            std::string errorstr =  error.what();
            Logger::Error("SScript::Update " + errorstr);
        }
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

void SetEntityPosition(Entity entity, float x, float y)
{
    if(!entity.HasComponent<CTransform>())
    {
        Logger::Error("SScript::SetEntityPosition : entity has NOT CTransform");
        return;
    }
    auto& transform = entity.GetComponent<CTransform>();
    transform.position = {x,y};
}

std::tuple<double, double> GetEntityVelocity(Entity entity)
{
    if(!entity.HasComponent<CRigidBody>())
    {
        Logger::Error("SScript::GetEntityVelocity : entity has NOT CRigidBody");
        return {0.0,0.0};
    }
    auto& rigidbody = entity.GetComponent<CRigidBody>();
    return {rigidbody.velocity.x,rigidbody.velocity.y};
}

void SetEntityVelocity(Entity entity, double x, double y)
{
    if(!entity.HasComponent<CRigidBody>())
    {
        Logger::Error("SScript::GetEntityVelocity : entity has NOT CRigidBody");
        return;
    }
    auto& rigidbody = entity.GetComponent<CRigidBody>();
    rigidbody.velocity = {x,y};
}

double GetEntityRotation(Entity entity)
{
    if(!entity.HasComponent<CTransform>())
    {
        Logger::Error("SScript::GetEntityRotation : entity has NOT CTransform");
        return 0.0f;
    }
    auto& transform = entity.GetComponent<CTransform>();
    return transform.rotation.asDegrees();
}

void SetEntityRotation(Entity entity, double angle)
{
    if(!entity.HasComponent<CTransform>())
    {
        Logger::Error("SScript::SetEntityRotation : entity has NOT CTransform");
        return;
    }
    auto& transform = entity.GetComponent<CTransform>();
    transform.rotation = sf::degrees(angle);
}

std::tuple<double, double> GetProjectileVelocity(Entity entity)
{
   if(!entity.HasComponent<CShootEmitter>())
    {
        Logger::Error("SScript::GetProjectileVelocity : entity has NOT CShootEmitter");
        return {0.f,0.f};
    }
    auto& projectile = entity.GetComponent<CShootEmitter>();
    return {projectile.velocity.x,projectile.velocity.y};
}

void SetProjectileVelocity(Entity entity, double x, double y)
{
    if(!entity.HasComponent<CShootEmitter>())
    {
        Logger::Error("SScript::SetProjectileVelocity : entity has NOT CShootEmitter");
    }
    auto& projectile = entity.GetComponent<CShootEmitter>();
    projectile.velocity = {x,y};
}

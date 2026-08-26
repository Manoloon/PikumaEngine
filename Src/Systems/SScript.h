#pragma once

#include <sol/sol.hpp>
#include "../Components/Components.h"
#include "../ECS/ECS.h"

std::tuple<double,double> GetEntityPosition(Entity entity);
void SetEntityPosition(Entity entity, float x, float y);

std::tuple<double,double> GetEntityVelocity(Entity entity);
void SetEntityVelocity(Entity entity, double x, double y);

double GetEntityRotation(Entity entity);
void SetEntityRotation(Entity entity, double angle);

std::tuple<double,double> GetProjectileVelocity(Entity entity);
void SetProjectileVelocity(Entity entity, double x, double y);

class SScript : public System
{
    public:
    SScript();
    void Update(float DeltaTime,float ellapsed_time);
    void CreateBindings(sol::state& lua);
};
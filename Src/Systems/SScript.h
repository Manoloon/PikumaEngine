#pragma once

#include <sol/sol.hpp>
#include "../Components/Components.h"
#include "../ECS/ECS.h"

std::tuple<double,double> GetEntityPosition(Entity entity);
void SetEntityPosition(Entity entity, double x, double y);

class SScript : public System
{
    public:
    SScript();
    void Update();
    void CreateBindings(sol::state& lua);
};
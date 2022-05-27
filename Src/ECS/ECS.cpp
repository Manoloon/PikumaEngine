//
// Created by Manoloon on 26/05/2022.
//
#include <algorithm>
#include "ECS.h"

int Entity::GetId() const
{
    return id;
}

void System::AddEntityToSystem(const Entity& newEntity)
{
   entities.push_back(newEntity);
}

void System::RemoveEntityFromSystem(Entity EntityRef)
{
    if(entities.empty())
    {
        return;
    }
    entities.erase(std::remove_if(entities.begin(), entities.end(),
                                  [&EntityRef](Entity other)
                                  {
                                    return EntityRef.GetId() == other.GetId();
                                  }),entities.end());
}

std::vector<Entity> System::GetEntities() const
{
    return entities;
}

const Signature& System::GetComponentSignature() const
{
    return componentSignature;
}

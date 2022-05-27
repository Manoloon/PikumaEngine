//
// Created by Manoloon on 26/05/2022.
//
#include "ECS.h"

int Entity::GetId() const
{
    return id;
}

void System::AddEntityToSystem(Entity newEntity)
{

}

void System::RemoveEntityFromSystem(Entity EntityRef)
{

}

std::vector<Entity> System::GetEntities() const
{
    return entities;
}

const Signature& System::GetComponentSignature() const
{
    return componentSignature;
}

int Component::GetId() const
{
    return id;
}

//
// Created by Manoloon on 26/05/2022.
//
#include <algorithm>
#include "ECS.h"

// initialize the interface variable for the static function.
int IComponent::nextId =0;

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
                                    return EntityRef == other;
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

Entity Registry::CreateEntity()
{
    int entityID = numEntities++;
    if(entityID >= componentSignatures.size())
    {
        componentSignatures.resize(entityID+1);
    }
    Entity entity(entityID);
    entitiesToAdd.insert(entity);
    Logger::Warning("Entity added"+ std::to_string(entityID));
    return entity;
}

void Registry::Update()
{

}

void Registry::AddEntityToSystem(Entity entity)
{

}


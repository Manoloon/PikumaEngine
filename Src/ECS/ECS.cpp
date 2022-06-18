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
void System::AddEntityToSystem(Entity newEntity)
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

std::vector<Entity> System::GetSystemEntities() const
{
    return entities;
}

const Signature& System::GetComponentSignature() const
{
    return componentSignature;
}

Entity Registry::CreateEntity()
{
    int entityID;
    entityID = numEntities++;
    if(entityID >= componentSignatures.size())
    {
        componentSignatures.resize(entityID+1);
    }
    Entity entity(entityID);
    entity.registry = this;
    entitiesToAdd.insert(entity);
    if(entityID >=componentSignatures.size())
    {
        componentSignatures.resize(entityID +1);
    }
    return entity;
}

void Registry::Update()
{
    for(auto entity : entitiesToAdd)
    {
        AddEntityToSystem(entity);
    }
    entitiesToAdd.clear();
}

void Registry::AddEntityToSystem(Entity entity)
{
    const auto entityId = entity.GetId();
    const auto& entityCompSignature = componentSignatures[entityId];
    for(auto const& [key,system] : Systems)
    {
        const auto& systemCompSignature = system->GetComponentSignature();
        // a bitwise compare
        bool isInteresting = (entityCompSignature & systemCompSignature) == systemCompSignature;
        if(isInteresting)
        {
            system->AddEntityToSystem(entity);
        }
    }
}


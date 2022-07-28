//
// Created by Manoloon on 26/05/2022.
//
#include <algorithm>
#include "ECS.h"

// initialize the interface variable for the static function.
int IComponent::nextId =0;
////////////// Entity ///////////////////////////////
void Entity::Destroy()
{
    registry->DestroyEntity(*this);
}

int Entity::GetId() const
{
    return id;
}

////////////// SYSTEMS ///////////////////////////////
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
    if(freeEntityIds.empty())
    {
        entityID = numEntities++;
        if(entityID >= componentSignatures.size())
        {
            componentSignatures.resize(entityID+1);
        }
    }
    else
    {
        entityID = freeEntityIds.front();
        freeEntityIds.pop_front();
    }
    Entity entity(entityID);
    entity.registry = this;
    entitiesToAdd.insert(entity);
    return entity;
}

void Registry::DestroyEntity(Entity entity)
{
    entitiesToDestroy.insert(entity);
}
void Registry::Update()
{
    for(auto entity : entitiesToAdd)
    {
        AddEntityToSystem(entity);
    }
    entitiesToAdd.clear();
    for(auto entity : entitiesToDestroy)
    {
        RemoveEntityFromSystems(entity);
        componentSignatures[entity.GetId()].reset();
        freeEntityIds.push_back(entity.GetId());
    }
    entitiesToDestroy.clear();
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
void Registry::RemoveEntityFromSystems(Entity entity) const
{
    for(const auto& system : Systems)
    {
        system.second->RemoveEntityFromSystem(entity);
    }
}

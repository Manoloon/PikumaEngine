//
// Created by Manoloon on 26/05/2022.
//
#include <algorithm>
#include <string>
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
void Entity::Tag(const std::string& tag)
{
    registry->TagEntity(*this,tag);
}

bool Entity::HasTag(const std::string& tag) const
{
    return registry->EntityHasTag(*this,tag);
}

void Entity::Group(const std::string& group)
{
    registry->GroupEntity(*this,group);
}

bool Entity::BelongToGroup(const std::string& group) const
{
    return registry->EntityBelongToGroup(*this,group);
}
/////////////// REGISTRY //////////////////////////////

void Registry::TagEntity(Entity entity,const std::string& tag)
{
    entityPerTag.emplace(tag,entity);
    tagPerEntity.emplace(entity.GetId(),tag);
}

bool Registry::EntityHasTag(Entity entity,const std::string& tag) const
{
    if (tagPerEntity.find(entity.GetId()) == tagPerEntity.end())
    {
        return false;
    }
    return entityPerTag.find(tag)->second == entity;
}

Entity Registry::GetEntityByTag(const std::string& tag) const
{
    return entityPerTag.at(tag);
}

void Registry::RemoveEntityTag(Entity entity)
{
    auto taggedEntity = tagPerEntity.find(entity.GetId());
    if(taggedEntity != tagPerEntity.end())
    {
        auto tag = taggedEntity->second;
        entityPerTag.erase(tag);
        tagPerEntity.erase(taggedEntity);
    }
}

void Registry::GroupEntity(Entity entity,const std::string& group)
{
    entitiesPerGroup.emplace(group,std::set<Entity>());
    entitiesPerGroup[group].emplace(entity);
    groupPerEntity.emplace(entity.GetId(),group);
}

bool Registry::EntityBelongToGroup(const Entity& entity,const std::string& group) const
{
    if(entitiesPerGroup.empty())
    {
        Logger::Error("EntitiesPerGroup is Empty");
        return false;
    }
    if(entitiesPerGroup.find(group) == entitiesPerGroup.end())
    {
       Logger::Error("EntitiesPerGroup dont have a group name");
       std::cout << std::endl;
       std::cout << group << std::endl;
        return false; 
    }
    auto groupEntities = entitiesPerGroup.at(group);
    // TODO : See this if we can use the id
    std::string idString = std::to_string(entity.GetId());
    return groupEntities.find(entity) != groupEntities.end();
}

std::vector<Entity> Registry::GetEntitiesByGroup(const std::string& group) const
{
    auto& setOfEntities = entitiesPerGroup.at(group);
    return {setOfEntities.begin(),setOfEntities.end()};
}

void Registry::RemoveEntityGroup(Entity entity)
{
    auto groupedEntity = groupPerEntity.find(entity.GetId());
    if(groupedEntity != groupPerEntity.end())
    {
        auto group = groupedEntity->second;
        entitiesPerGroup.erase(group);
        groupPerEntity.erase(groupedEntity);
    }
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
    entities.erase(std::remove_if(std::begin(entities),std::end(entities),
                                  [&EntityRef](Entity other)
                                  {
                                    return EntityRef == other;
                                  }),std::end(entities));
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
        if(entityID >= (int)componentSignatures.size())
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

        //remove the entity from the components pools
        for(auto pool : componentsPools)
        {
            if(pool != nullptr)
            {
                pool->RemoveEntityFromPool(entity.GetId());
            }
        }

        freeEntityIds.push_back(entity.GetId());

        RemoveEntityTag(entity);
        RemoveEntityGroup(entity);
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

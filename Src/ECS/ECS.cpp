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
    int id = entity.GetId();
    auto found = entityPerTag.find(tag);
    if(found != nullptr)
    {
        throw std::runtime_error("Cant be more than one entity per tag" + tag);
    }
    entityPerTag.emplace(tag,entity);

    tagPerEntity.emplace(id,tag);
}

bool Registry::EntityHasTag(Entity entity,const std::string& tag) const
{
    auto result = GetEntityByTag(tag);
    return result.has_value() && *result == entity;
}

std::optional<Entity> Registry::GetEntityByTag(const std::string& tag) const
{
    auto result = entityPerTag.find(tag);
    if(result == std::cend(entityPerTag))
    {
        return std::nullopt;
    }
    return result->second;
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
    //Logger::Info("Registry::GroupEntity group to add : " + group);
    entitiesPerGroup[group].emplace(entity);
    //Logger::Info("Registry::GroupEntity groupPerEntity to add id: " + std::to_string(entity.GetId()) + " group: " + group);
    groupPerEntity[entity.GetId()] = group;
}

bool Registry::EntityBelongToGroup(const Entity& entity,const std::string& group) const
{
    if(entitiesPerGroup.empty())
    {
        Logger::Error("Registry::EntitiesPerGroup is Empty");
        return false;
    }
    if(entitiesPerGroup.find(group) == entitiesPerGroup.end())
    {
       //Logger::Error("Registry::EntitiesPerGroup dont have a group name" + group);
        return false; 
    }
    const auto& groupEntities = entitiesPerGroup.at(group);
    return groupEntities.find(entity) != groupEntities.end();
}

std::vector<Entity> Registry::GetEntitiesByGroup(const std::string& group) const
{
    auto it = entitiesPerGroup.find(group);
    if(it == std::cend(entitiesPerGroup))
    {
        return {};
    }
    return {it->second.begin(),it->second.end()};
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
    entities.erase(std::remove_if(std::begin(entities),std::end(entities),[&EntityRef](Entity other)
    {
        return EntityRef == other;
    }),
    std::end(entities));
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

        RemoveEntityTag(entity);
        RemoveEntityGroup(entity);
        freeEntityIds.emplace_back(entity.GetId());
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

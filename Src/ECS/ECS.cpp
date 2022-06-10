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

template<typename T, typename... TArgs>
void Registry::AddComponent(Entity entity, TArgs &&... args)
{
    const auto componentId = Component<T>::GetId();
    const auto entityId = entity.GetId();
    // if the new component its not in the component Pool -> resize componentPool and init with
    // nullptr
    if(componentId >= componentsPool.size())
    {
        componentsPool.resize(componentId + 1, nullptr);
    }
    // if the new component dont exist in the componentPool
    // create a new one and place it in the ComponentsPool
    if(!componentsPool[componentId])
    {
        auto newCompPool = new Pool<T>();
        componentsPool[componentId] = newCompPool;
    }
    // get the pool of components for that component value
    Pool<T>* compPool = Pool<T>(componentsPool[componentId]);
    // if the entity id is greater than the current size of the pool , resize the pool
    if(entityId >= compPool->GetSize())
    {
        compPool->Resize(numEntities);
    }
    //create a new component of type T and forward the many parameters to the constructor.
    T newComponent(std::forward<TArgs>(args)...);
    // add the new component to the pool list, using the identity id as index
    compPool->Set(entityId,newComponent);
    // change the compoent signature of the entity and set the component id on the bitset to 1
    componentSignatures[entityId].set(componentId);
}

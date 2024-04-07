//
// Created by Manoloon on 26/05/2022.
//
#pragma once

#include <bitset>
#include <vector>
#include <set>
#include <string>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <deque>
#include "../Src/Logger.h"
#include "../Components/Components.h"

const unsigned int MAX_COMPONENTS =32;
using Signature  = std::bitset<MAX_COMPONENTS>;
//interface for components
struct IComponent
{
protected:
    //as this is an static function, I need to always initialize the value
    // this is is in the cpp.
    static int nextId;
};

template<typename TComponent>
class Component : public IComponent
{
public:
    static int GetId()
    {
        static int id = nextId++;
        return id;
    }
};
////////////////////////////////////////////////////////////////////////////////
// Entity
////////////////////////////////////////////////////////////////////////////////
// An entity is an Actor.
////////////////////////////////////////////////////////////////////////////////
class Entity
{
public:
    int id;
    class Registry* registry;

    Entity(const Entity& entity)=default;
    explicit Entity(int newId,class Registry* newRegistry= nullptr) : id(newId),registry(newRegistry){}
    void Destroy();
    [[nodiscard]] int GetId() const;
    Entity& operator = (const Entity& other) = default;
    bool operator == (const Entity& other) const {return id == other.GetId();}
    bool operator != (const Entity& other) const {return id != other.GetId();}
    bool operator >(const Entity& other) const { return id > other.id; }
    bool operator <(const Entity& other) const { return id < other.id; }

    // Tag system
    void Tag(const std::string& tag);
    bool HasTag(const std::string& tag) const;
    void Group(const std::string& group);
    bool BelongToGroup(const std::string& group)const;

    template<typename TComponent,typename  ...TArgs>
        void AddComponent(TArgs&& ...args);
    template<typename TComponent>
        void RemoveComponent();
    template<typename TComponent>
        bool HasComponent() const ;
    template<typename TComponent>
        TComponent& GetComponent() const;
};
////////////////////////////////////////////////////////////////////////////////
// System
////////////////////////////////////////////////////////////////////////////////
// The system processes entities that contain a specific signature
////////////////////////////////////////////////////////////////////////////////
class System
{
    Signature componentSignature;
    std::vector<Entity> entities;
public:
    void AddEntityToSystem(Entity newEntity);
    void RemoveEntityFromSystem(Entity EntityRef);

    std::vector<Entity> GetSystemEntities() const;

    const Signature& GetComponentSignature() const;

    template<typename TComponent>void RequireComponent();
};
////////////////////////////////////////////////////////////////////////////////
// Pool
////////////////////////////////////////////////////////////////////////////////
// A pool is just a vector (contiguous data) of objects of type T
////////////////////////////////////////////////////////////////////////////////
class IPool
{
public:
    virtual void RemoveEntityFromPool(int entityId)=0;
};

template<typename T>
class Pool : public IPool
{
private:
    std::vector<T> Data;
    int PoolSize = 0;
    std::unordered_map<int,int> IdToIndex;
    std::unordered_map<int,int> IndexToId;

public:
    explicit Pool(int capacity = 100)
    { Data.resize(capacity); }

    bool IsEmpty() const { return PoolSize == 0; }

    size_t GetCapacity() const  { return Data.size(); }

    void Resize(size_t Capacity) { Data.resize(Capacity); }

    void Clear() 
    {
        Data.clear();
        IdToIndex.clear();
        IndexToId.clear();
        PoolSize = 0;
    }

    void Add(T object) { Data.push_back(object); }

    void Set(int EntityId, T object) 
    {
        // if the id exists
        if(IdToIndex.find(EntityId) != std::end(IdToIndex))
        {
            int index = IdToIndex[EntityId];
            Data[index] = object;
        }
        else
        {
            // use size as the last index in the array.
            int index = PoolSize;
            IdToIndex.emplace(EntityId,index); 
            IndexToId.emplace(index,EntityId);
            if(index >= (int)Data.size())
            {
                Data.resize(index * 2);
            }
            Data[index] = object;
            PoolSize++;
        }
    }

    void Remove(int EntityId)
    {
        // move the last value to the place where the removed one was.
        int indexToRemove = IdToIndex[EntityId];
        int lastIndex = PoolSize - 1;
        Data[indexToRemove] = Data[lastIndex];

        // then we reflect the changes into the other arrays.
        int idLastElement = IndexToId[lastIndex];
        IdToIndex[idLastElement] = indexToRemove;
        IndexToId[indexToRemove] = idLastElement;

        // now we remove the object that we want to remove.
        IdToIndex.erase(EntityId);
        IndexToId.erase(EntityId);
        PoolSize--;
    }

    void RemoveEntityFromPool(int entityId) override
    {
        if(IdToIndex.find(entityId) != std::end(IdToIndex))
        {
            Remove(entityId);
        }
    }

    T& Get(int EntityId) 
    { 
        int index = IdToIndex[EntityId];
        return static_cast<T&>(Data[index]); 
    }

    T &operator[](unsigned int index) { return Data[index]; }
};
////////////////////////////////////////////////////////////////////////////////
// Registry
////////////////////////////////////////////////////////////////////////////////
// The registry manages the creation and destruction of entities, add systems,
// and components.
////////////////////////////////////////////////////////////////////////////////
class Registry
{
    int numEntities=0;
    // vector index = component type ID
    // Pool index = Identity ID
    std::vector<std::shared_ptr<IPool>> componentsPools;
    std::vector<Signature> componentSignatures;
    std::set<Entity> entitiesToAdd;
    std::set<Entity> entitiesToDestroy;
    std::unordered_map<std::type_index,std::shared_ptr<System>> Systems;
    std::deque<int> freeEntityIds;

    std::unordered_map<std::string, Entity> entityPerTag;
    std::unordered_map<int,std::string> tagPerEntity;

    std::unordered_map<std::string, std::set<Entity>> entitiesPerGroup;
    std::unordered_map<int,std::string> groupPerEntity;

public:
    Entity CreateEntity();
    void DestroyEntity(Entity entity);
    void AddEntityToSystem(Entity entity);
    void RemoveEntityFromSystems(Entity entity) const;

    // tag management
    void TagEntity(Entity entity,const std::string& tag);
    bool EntityHasTag(Entity entity,const std::string& tag) const;
    Entity GetEntityByTag(const std::string& tag) const;
    void RemoveEntityTag(Entity entity);

    // group management
    void GroupEntity(Entity entity,const std::string& group);
    bool EntityBelongToGroup(const Entity& entity,const std::string& group) const;
    std::vector<Entity> GetEntitiesByGroup(const std::string& group) const;
    void RemoveEntityGroup(Entity entity);

    void Update();

    template <typename TComponent,typename ...TArgs>
        void AddComponent(Entity entity, TArgs&& ...args);
    template<typename TComponent>
        void RemoveComponent(Entity entity);
    template<typename TComponent>
        bool HasComponent(Entity entity) const;
    template<typename TComponent>
        TComponent& GetComponent(Entity entity) const;

    // systems
    template<typename TSystem, typename ...TArgs>
        void AddSystem(TArgs&& ...args);
    template<typename TSystem>
        void RemoveSystem();
    template<typename TSystem>
        bool HasSystem() const;
    template<typename TSystem>
        TSystem& GetSystem() const;
};

// Templates //
//every template function should be implement in the header file.
// the impl of a template goes on the Header file.
template<typename TComponent>
void System::RequireComponent()
{
    const auto componentID = Component<TComponent>::GetId();
    componentSignature.set(componentID);
}

template<typename TComponent, typename... TArgs>
void Registry::AddComponent(Entity entity, TArgs &&... args)
{
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();
    // if the new component its not in the component Pool -> resize componentPool and init with
    // nullptr
    if(componentId >= (int)(componentsPools.size()))
    {
        componentsPools.resize(componentId + 1, nullptr);
    }
    // if the new component don´t exist in the componentPool
    // create a new one and place it in the ComponentsPool
    if(!componentsPools[componentId])
    {
        std::shared_ptr<Pool<TComponent>> newCompPool = std::make_shared<Pool<TComponent>>();
        componentsPools[componentId] = newCompPool;
    }
    // get the pool of components for that component value
    std::shared_ptr<Pool<TComponent>> compPool = std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentId]);
    //create a new component of type T and forward the many parameters to the constructor.
    TComponent newComponent(std::forward<TArgs>(args)...);
    // add the new component to the pool list, using the identity id as index
    compPool->Set(entityId, newComponent);
    // change the component signature of the entity and set the component id on the bitset to 1
    componentSignatures[entityId].set(componentId);

    std::cout << "Component ID = " << componentId << "--> Pool Size : " << compPool->GetCapacity() << std::endl;

}

template<typename TComponent>
void Registry::RemoveComponent(Entity entity)
{
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();
    // search the component pool
    std::shared_ptr<Pool<TComponent>> newCompPool = std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentId]);
    newCompPool->Remove(entityId);
    componentSignatures[entityId].set(componentId,false);
}

template<typename TComponent>
bool Registry::HasComponent(Entity entity) const
{
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();
    return componentSignatures[entityId].test(componentId);
}

template<typename TComponent>
TComponent& Registry::GetComponent(Entity entity) const
{
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();
    auto newCompPool = std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentId]);
    return newCompPool->Get(entityId);
}

template<typename TSystem, typename... TArgs>
void Registry::AddSystem(TArgs&& ...args)
{
 std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
 Systems.insert(std::make_pair(std::type_index(typeid(TSystem)),newSystem));
}

template<typename TSystem>
void Registry::RemoveSystem()
{
    auto system = Systems.find(std::type_index(typeid(TSystem)));
    Systems.erase(system);
}

template<typename TSystem>
bool Registry::HasSystem() const
{
    return Systems.find(std::type_index(typeid(TSystem))) != Systems.end();
}

template<typename TSystem>
TSystem &Registry::GetSystem() const
{
    auto system = Systems.find(std::type_index(typeid(TSystem)));
    // I need to dereference the iterator of the system I found
    return *(std::static_pointer_cast<TSystem>(system->second));
}

template<typename TComponent, typename... TArgs>
void Entity::AddComponent(TArgs &&... args)
{
    registry->AddComponent<TComponent>(*this,std::forward<TArgs>(args)...);
}

template<typename TComponent>
void Entity::RemoveComponent()
{
    registry->RemoveComponent<TComponent>(*this);
}

template<typename TComponent>
bool Entity::HasComponent() const
{
    return registry->HasComponent<TComponent>(*this);
}

template<typename TComponent>
    TComponent& Entity::GetComponent() const
{
    return registry->GetComponent<TComponent>(*this);
}

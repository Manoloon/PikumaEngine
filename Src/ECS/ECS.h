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
    virtual ~IPool() = default;
};

template<typename T>
class Pool : public IPool
{
private:
    std::vector<T> data;
public:
    explicit Pool(int size = 100)
    { data.resize(size); }

    bool IsEmpty() const { return data.empty(); }

    size_t GetSize() const  { return data.size(); }

    void Resize(size_t size) { data.resize(size); }

    void Clear() { data.clear(); }

    void Add(T object) { data.push_back(object); }

    void Set(int index, T object) { data[index] = object; }

    T& Get(int index) { return static_cast<T&>(data[index]); }

    T &operator[](unsigned int index) { return data[index]; }
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
    std::vector<std::shared_ptr<IPool>> componentsPool;
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
    if(componentId >= componentsPool.size())
    {
        componentsPool.resize(componentId + 1, nullptr);
    }
    // if the new component don´t exist in the componentPool
    // create a new one and place it in the ComponentsPool
    if(!componentsPool[componentId])
    {
        std::shared_ptr<Pool<TComponent>> newCompPool = std::make_shared<Pool<TComponent>>();
        componentsPool[componentId] = newCompPool;
    }
    // get the pool of components for that component value
    std::shared_ptr<Pool<TComponent>> newCompPool = std::static_pointer_cast<Pool<TComponent>>
                                                                    (componentsPool[componentId]);
    // if the entity id is greater than the current size of the pool , resize the pool
    if(entityId >= newCompPool->GetSize())
    {
        newCompPool->Resize(numEntities);
    }
    //create a new component of type T and forward the many parameters to the constructor.
    TComponent newComponent(std::forward<TArgs>(args)...);
    // add the new component to the pool list, using the identity id as index
    newCompPool->Set(entityId, newComponent);
    // change the component signature of the entity and set the component id on the bitset to 1
    componentSignatures[entityId].set(componentId);
}

template<typename TComponent>
void Registry::RemoveComponent(Entity entity)
{
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();
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
    auto newCompPool = std::static_pointer_cast<Pool<TComponent>>(componentsPool[componentId]);
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

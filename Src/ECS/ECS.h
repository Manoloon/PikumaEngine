//
// Created by Manoloon on 26/05/2022.
//

#ifndef PIKUMAENGINE_ECS_H
#define PIKUMAENGINE_ECS_H

#include <bitset>
#include <vector>
#include <set>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "../Src/Logger.h"

const unsigned int MAX_COMPONENTS =32;
typedef std::bitset<MAX_COMPONENTS> Signature;

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
        static auto id = nextId++;
        return id;
    }
};
class Entity
{
    int id;
public:
    explicit Entity(int newId) : id(newId)
    {}

    int GetId() const;
    Entity& operator = (const Entity& other) = default;
    bool operator == (const Entity& other) const {return id == other.GetId();}
    bool operator != (const Entity& other) const {return id != other.GetId();}
    bool operator >(const Entity& other) const { return id > other.id; }
    bool operator <(const Entity& other) const { return id < other.id; }

    template<typename TComponent,typename  ...TArgs>
        void AddComponent(TArgs&& ...args);

    template<typename TComponent>
        void RemoveComponent();

    template<typename TComponent>
        bool HasComponent() const ;

    template<typename TComponent>
        TComponent& GetComponent();
    class Registry* registry;
};
class System
{
    Signature componentSignature;
    std::vector<Entity> entities;
public:
    void AddEntityToSystem(const Entity& newEntity);

    void RemoveEntityFromSystem(Entity EntityRef);

    std::vector<Entity> GetEntities() const;

    const Signature &GetComponentSignature() const;

    template<typename TComponent>void RequireComponent();
};

// interface para las pools
class IPool
{
public:
    virtual ~IPool() = default;
};

template<class T>
class Pool : public IPool
{
private:
    std::vector<T> data;
public:
    explicit Pool(int size = 100)
    { data.resize(size); }

    virtual ~Pool() = default;

    bool IsEmpty() const { return data.empty(); }

    size_t GetSize() const  { return data.size(); }

    void Resize(size_t size) { data.resize(size); }

    void Clear() { data.clear(); }

    void Add(T object) { data.push_back(object); }

    void Set(int index, T object) { data[index] = object; }

    T &Get(int index) const { return static_cast<T>(data[index]); }

    T &operator[](unsigned int index) { return data[index]; }
};

class Registry
{
    int numEntities=0;
    // vector index = component type ID
    // Pool index = Identity ID
    std::vector<std::shared_ptr<IPool>> componentsPool;
    std::vector<Signature> componentSignatures;
    std::set<Entity> entitiesToAdd;
    std::set<Entity> entitiesToKill;
    std::unordered_map<std::type_index,std::shared_ptr<System>> Systems;
public:
    template <typename TComponent,typename ...TArgs>
        void AddComponent(Entity entity, TArgs&& ...args);
    template<typename TComponent>
        void RemoveComponent(Entity entity);
    template<typename TComponent>
        bool HasComponent(Entity entity) const;
    template<typename TComponent>
        TComponent& GetComponent(Entity entity) const;

    Entity CreateEntity();
    void AddEntityToSystem(Entity entity);
    void Tick();

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
void Registry::AddSystem(TArgs &&... args)
{
 std::shared_ptr<TSystem*> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
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
TComponent &Entity::GetComponent()
{
    return registry->GetComponent<TComponent>(*this);
}

#endif //PIKUMAENGINE_ECS_H

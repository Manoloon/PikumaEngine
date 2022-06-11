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

    int GetSize() const  { return data.size(); }

    void Resize(int size) { data.resize(size); }

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
    std::vector<IPool*> componentsPool;
    std::vector<Signature> componentSignatures;
    std::set<Entity> entitiesToAdd;
    std::set<Entity> entitiesToKill;
    std::unordered_map<std::type_index,System*> Systems;
public:
    // remove entity
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
    void Update();
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
        // TODO : change to smartptr
        auto newCompPool = new Pool<TComponent>();
        componentsPool[componentId] = newCompPool;
    }
    // get the pool of components for that component value
    Pool<TComponent>* newCompPool = Pool<TComponent>(componentsPool[componentId]);
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

#endif //PIKUMAENGINE_ECS_H

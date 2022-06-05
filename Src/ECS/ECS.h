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
    // add component
    // remove component
    Entity CreateEntity();
    void AddEntityToSystem(Entity entity);
    void Update();
};

// the impl of a template goes on the Header file.
template<typename TComponent>
void System::RequireComponent()
{
    const auto componentID = Component<TComponent>::GetId();
    componentSignature.set(componentID);
}

#endif //PIKUMAENGINE_ECS_H

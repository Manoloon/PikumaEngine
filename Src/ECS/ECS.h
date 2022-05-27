//
// Created by Manoloon on 26/05/2022.
//

#ifndef PIKUMAENGINE_ECS_H
#define PIKUMAENGINE_ECS_H

#include <bitset>
#include <vector>

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
};
class System
{
    Signature componentSignature;
    std::vector<Entity> entities;
public:
    void AddEntityToSystem(Entity newEntity);

    void RemoveEntityFromSystem(Entity EntityRef);

    std::vector<Entity> GetEntities() const;

    const Signature &GetComponentSignature() const;

    template<typename TComponent>void RequireComponent();
};

class Registry
{

};

// the impl of a template goes on the Header file.
template<typename TComponent>
void System::RequireComponent()
{
    const auto componentID = Component<TComponent>::GetId();
    componentSignature.set(componentID);
}

#endif //PIKUMAENGINE_ECS_H

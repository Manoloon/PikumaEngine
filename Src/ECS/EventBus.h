//
// Created by Manoloon on 28/07/2022.
//

#ifndef PIKUMAENGINE_EVENTBUS_H
#define PIKUMAENGINE_EVENTBUS_H

#include <map>
#include <typeindex>
#include <memory>
#include <list>
#include <functional>
#include "../Events/Event.h"

//interface
class IEventCallback
{
private:
    virtual void Call(Event& event)=0;
public:
    virtual ~IEventCallback()=default;
    void Execute(Event& event)
    {
        Call(event);
    }
};

// Wrapper
template<typename TOwner,typename TEvent>
class EventCallback : public IEventCallback
{
    typedef void (TOwner::*CallbackFunction)(TEvent&);
    TOwner* ownerInstance;
    CallbackFunction  callbackFunction;

    virtual void Call(Event& event) override
    {
        std::invoke(callbackFunction,ownerInstance,static_cast<TEvent&>(event));
    }
public:
    EventCallback(TOwner* ownerInstance,CallbackFunction callbackFunction)
        :ownerInstance(ownerInstance),callbackFunction(callbackFunction){}

    virtual ~EventCallback() override=default;
};

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

/**
* susbcriber to an event type <TEvent>
* example : eventBus->SubscribeToEvent<CollisionEvent>(&Game::onCollision);
*/
class EventBus
{
    std::map<std::type_index,std::unique_ptr<HandlerList>> subscribers;
public:
    template<typename TEvent,typename TOwner>
    void SubscribeToEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&))
    {
        if(!subscribers[typeid(TEvent)].get())
        {
            subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
        }
        auto subscriber = std::make_unique<EventCallback<TOwner,TEvent>>(ownerInstance,
                                                                        callbackFunction);
        subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
    }

    template<typename TEvent,typename ...TArgs>
    void EmitEvent(TArgs&& ...args)
    {
        auto handlers = subscribers[typeid(TEvent)].get();
        if(handlers)
        {
            for(auto it = handlers->begin();it != handlers->end();it++)
            {
                auto handler = it->get();
                TEvent event(std::forward<TArgs>(args)...);
                handler->Execute(event);
            }
        }
    }
    void Reset()
    {
        subscribers.clear();
    }
};

#endif //PIKUMAENGINE_EVENTBUS_H

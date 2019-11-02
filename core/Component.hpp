#pragma once

#include <map>
#include "BaseMessage.hpp"

namespace Core
{
    class Object;
    
    enum class ComponentType
    {
        Transform = 0
    };
    
    class Component
    {
    public:
        ~Component();
        
        ComponentType GetComponentType() const { return componentType; }
        
        bool SendMessage(BaseMessage* msg);
        void RegisterMessage(MessageType type, std::function<void(BaseMessage*)> handler);
        
        friend Object;
        
    protected:
        Component(ComponentType componentType);
        
        void ProvideObject(std::shared_ptr<Object> object);
        
    private:
        ComponentType componentType;
        std::shared_ptr<Object> object;
        
        std::map<MessageType, std::function<void(BaseMessage*)>>* messageHandlers = nullptr;
    };
}

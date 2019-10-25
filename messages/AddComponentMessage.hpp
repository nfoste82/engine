#pragma once

#include <memory>
#include "../core/BaseMessage.hpp"
#include "../core/Component.hpp"

using namespace Core;

class AddComponentMessage : public BaseMessage
{
public:
    AddComponentMessage(int targetObjectID, Component* component) :
        BaseMessage(targetObjectID, MessageType::AddComponent),
        component(component)
    {}
    
    Component* GetComponent() { return component; }
    
private:
    Component* component;
};

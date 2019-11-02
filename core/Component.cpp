#include "Component.hpp"

using namespace Core;

Component::Component(ComponentType componentType) :
    componentType(componentType)
{
}
    
Component::~Component()
{
    if (messageHandlers != nullptr)
    {
        messageHandlers->clear();
    }
}

bool Component::SendMessage(BaseMessage* msg)
{
    if (messageHandlers == nullptr)
    {
        return false;
    }
    
    auto handler = messageHandlers->find(msg->GetType());
    if (handler != messageHandlers->end())
    {
        handler->second(msg);
    }
    
    return false;
}

void Component::RegisterMessage(MessageType type, std::function<void(BaseMessage*)> handler)
{
    if (messageHandlers == nullptr)
    {
        messageHandlers = new std::map<MessageType, std::function<void(BaseMessage*)>>();
    }
    
    (*messageHandlers)[type] = handler;
}

void Component::ProvideObject(std::shared_ptr<Object> object)
{
    if (this->object != nullptr)
    {
        throw "Object already provided to component.";
    }
    
    this->object = object;
}

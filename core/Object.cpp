#include "Object.hpp"

#include "Component.hpp"
#include "BaseMessage.hpp"
#include "../messages/AddComponentMessage.hpp"

namespace Core
{
    void Object::AddComponent(Component* component)
    {
        auto componentType = component->GetComponentType();
        
        if (componentLookup.find(componentType) != componentLookup.end())
        {
            throw "Component of type already exists.";
        }
        
        auto componentPtr = std::shared_ptr<Component>(component);
        componentLookup[componentType] = componentPtr;
        components.push_back(componentPtr);
    }
    
    bool Object::SendMessage(BaseMessage* msg)
    {
        switch (msg->GetType())
        {
            case MessageType::AddComponent:
                MsgHandlerAddComponent(static_cast<AddComponentMessage*>(msg));
                return true;
            default:
                // Check if components handle the message
                // TODO: This could be optimized by keeping a mapping of which components care about which messages
                for (auto c : components)
                {
                    c->SendMessage(msg);
                }
                break;
        }
        
        return false;
    }
    
    void Object::MsgHandlerAddComponent(AddComponentMessage* msg)
    {
        AddComponent(msg->GetComponent());
    }
}

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
        
        componentLookup[componentType] = std::shared_ptr<Component>(component);
    }
    
    bool Object::SendMessage(BaseMessage* msg)
    {
        switch (msg->GetType())
        {
            case MessageType::AddComponent:
                MsgHandlerAddComponent(static_cast<AddComponentMessage*>(msg));
                return true;
        }
        
        return false;
    }
    
    void Object::MsgHandlerAddComponent(AddComponentMessage* msg)
    {
        AddComponent(msg->GetComponent());
    }
}

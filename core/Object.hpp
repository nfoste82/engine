#pragma once

#include <memory>
#include <vector>
#include <map>
#include "Component.hpp"

class AddComponentMessage;

namespace Core
{
class BaseMessage;
    
class Object
{
public:
    Object(int uniqueID) : id(uniqueID)
    {
    }

    int GetID() const { return id; }
    
    void AddComponent(Component* component);
    bool HasComponent(ComponentType type) const { return componentLookup.find(type) != componentLookup.end(); }
    
    bool SendMessage(BaseMessage* msg);

private:
    void MsgHandlerAddComponent(AddComponentMessage* msg);
    
private:
    int id;
    std::vector<std::shared_ptr<Component>> components;
    std::map<ComponentType, std::shared_ptr<Component>> componentLookup;
};
}

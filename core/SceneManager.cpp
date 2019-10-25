#include <iostream>
#include "SceneManager.hpp"
#include "BaseMessage.hpp"

namespace Core
{
int SceneManager::s_nextObjectID = 0;

SceneManager::~SceneManager()
{
    std::cout << objects.size() << " Objects were still alive and are being destroyed as SceneManager is destroyed." << std::endl;
}

const Object& SceneManager::CreateObject()
{
    std::shared_ptr<Object> newObj = std::make_shared<Object>(s_nextObjectID++);

    // Add to the vector
    objects.push_back(newObj);
    
    // Add to the map that allows fast lookup by ID
    objectsByID[newObj->GetID()] = newObj;

    return *newObj;
}

const Object& SceneManager::FindObjectByID(int id)
{
    auto it = objectsByID.find(id);
    if (it != objectsByID.end())
    {
        return *it->second;
    }
    
    throw "No Object Found By ID";
}

// Returns true if the object or any components handled the message
bool SceneManager::SendMessage(BaseMessage* msg)
{
    // We look for the object in the scene by its ID
    auto objIt = objectsByID.find(msg->GetTargetObjectID());
    if (objIt != objectsByID.end())
    {
        // Object was found, so send it the message
        return objIt->second->SendMessage(msg);
    }
    
    // Object with the specified ID wasn't found
    return false;
}
}

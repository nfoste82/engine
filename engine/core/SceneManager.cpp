#include <iostream>
#include "SceneManager.h"

int SceneManager::s_nextObjectID = 0;

SceneManager::~SceneManager()
{
    std::cout << m_objects.size() << " Objects were still alive and are being destroyed as SceneManager is destroyed." << std::endl;
}

const Object& SceneManager::CreateObject()
{
    std::shared_ptr<Object> newObj = std::make_shared<Object>(s_nextObjectID++);

    // Add to the vector
    m_objects.push_back(newObj);
    
    // Add to the map that allows fast lookup by ID
    m_objectsByID[newObj->GetID()] = newObj;

    return *newObj;
}

const Object& SceneManager::FindObjectByID(int id)
{
    auto it = m_objectsByID.find(id);
    if (it != m_objectsByID.end())
    {
        return *it->second;
    }
    
    throw "No Object Found By ID";
}
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>
#include <map>
#include "Object.h"

class SceneManager
{
public:
    ~SceneManager();
    
    // // Returns true if the object or any components handled the message
    // bool SendMessage(BaseMessage* msg)
    // {
    //     // We look for the object in the scene by its ID
    //     std::map<int, Object*>::iterator objIt = m_Objects.find(msg->m_destObjectID);       
    //     if ( objIt != m_Objects.end() )
    //     {           
    //         // Object was found, so send it the message
    //         return objIt->second->SendMessage(msg);
    //     }
 
    //     // Object with the specified ID wasn't found
    //     return false;
    // }
 
    const Object& CreateObject();
    
    const Object& FindObjectByID(int it);
 
private:
    std::vector<std::shared_ptr<Object>> m_objects;
    std::map<int, std::shared_ptr<Object>> m_objectsByID;
    static int s_nextObjectID;
};

#endif //SCENEMANAGER_H
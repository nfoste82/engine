#pragma once

#include <memory>
#include <map>
#include "Object.hpp"

namespace Core
{
class BaseMessage;
    
class SceneManager
{
public:
    ~SceneManager();
    
    bool SendMessage(BaseMessage* msg);
     
    const Object& CreateObject();
    
    const Object& FindObjectByID(int it);
 
private:
    std::vector<std::shared_ptr<Object>> objects;
    std::map<int, std::shared_ptr<Object>> objectsByID;
    static int s_nextObjectID;
};
}

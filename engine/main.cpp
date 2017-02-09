#include <iostream>
#include "Vector3.h"
#include "SceneManager.h"
#include "Object.h"

int main()
{
    Vector3 customVec(1.f, 2.f, 3.f);

    std::cout << customVec << std::endl;
    
    SceneManager sceneMgr;
    const Object& firstObj = sceneMgr.CreateObject();
    
    std::cout << firstObj.GetID() << std::endl;
    
    const Object& secondObj = sceneMgr.CreateObject();
    
    std::cout << secondObj.GetID() << std::endl;
    
    sceneMgr.FindObjectByID(firstObj.GetID());
    
    try {
        sceneMgr.FindObjectByID(-1);
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
    
    std::cout << std::endl;
    return 0;
}
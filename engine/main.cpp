#include <iostream>
#include "Matrix3.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "SceneManager.h"
#include "Object.h"

void TestSceneManager()
{
    SceneManager sceneMgr;
    const Object& firstObj = sceneMgr.CreateObject();
    
    std::cout << firstObj.GetID() << std::endl;
    
    const Object& secondObj = sceneMgr.CreateObject();
    
    std::cout << secondObj.GetID() << std::endl;
    
    sceneMgr.FindObjectByID(firstObj.GetID());
    
    try
    {
        sceneMgr.FindObjectByID(-1);
    }
    catch (const char* msg)
    {
        std::cerr << msg << std::endl;
    }
}

void TestMath()
{
    Vector3 forward = Vector3::Forward;
    
    std::cout << "Forward vector: " << forward << std::endl;
    
    Matrix3 identityMatrix = Matrix3::Identity;
    
    std::cout << "Identity matrix: " << identityMatrix << std::endl;
    
    Vector3 fwdFromIdentityMat = identityMatrix.GetRollAxis();
    
    std::cout << "Forward vector for identity matrix: " << forward << std::endl;
    
    Quaternion quatFromMat = Quaternion::Identity;
    quatFromMat.FromRotationMatrix(identityMatrix);
    
    std::cout << "Quaternion from identity matrix: " << quatFromMat << std::endl;
}

int main()
{
    TestSceneManager();
    
    std::cout << std::endl;
    
    TestMath();
    
    std::cout << std::endl;
    return 0;
}
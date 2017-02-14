#include <iostream>
#include "Math.h"
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
    
    std::cout << std::endl;
    
    // Let's manually create a matrix that is rotated 90 degrees around the
    // world Y axis so that its forward is now (1, 0, 0), instead of (0, 0, 1)
    Matrix3 rotatedMatrix(Vector3(0.f, 0.f, -1.f),
                          Vector3::Up,
                          Vector3(1.f, 0.f, 0.f));
    
    std::cout << "Rotated matrix: " << rotatedMatrix << std::endl;
    
    std::cout << "Rotated matrix's forward: " << rotatedMatrix.GetRollAxis() << std::endl;
    
    quatFromMat.FromRotationMatrix(rotatedMatrix);
    
    std::cout << "Quaternion from rotated matrix: " << quatFromMat << std::endl;
    
    // Now we'll use Quaternion.FromAngleAxis to make the same quaternion.
    // This should rotate 90 degrees around the world Y axis just like we did
    // manually before.
    quatFromMat.FromAngleAxis(Math::HalfPi, Vector3::Up);
    
    std::cout << "Quaternion from FromAngleAxis: " << quatFromMat << std::endl;
    
    std::cout << std::endl;
    
    // Let's try it again, but we'll pitch -90 degrees so the matrix's forward
    // is facing in the same direction as the world up axis.
    rotatedMatrix = Matrix3(Vector3::Right,
                            Vector3(0.f, 0.f, -1.f),
                            Vector3(0.f, 1.f, 0.f));
    
    std::cout << "Rotated matrix: " << rotatedMatrix << std::endl;
    
    std::cout << "Rotated matrix's forward: " << rotatedMatrix.GetRollAxis() << std::endl;
    
    quatFromMat.FromRotationMatrix(rotatedMatrix);
    
    std::cout << "Quaternion from rotated matrix: " << quatFromMat << std::endl;
    
    // And again we'll use Quaternion.FromAngleAxis to make the same quaternion.
    // This should rotate -90 degrees around the X axis.
    quatFromMat.FromAngleAxis(-Math::HalfPi, Vector3::Right);
    
    std::cout << "Quaternion from FromAngleAxis: " << quatFromMat << std::endl;
}

int main()
{
    TestSceneManager();
    
    std::cout << std::endl;
    
    TestMath();
    
    std::cout << std::endl;
    return 0;
}
#include <iostream>
#include "Math.hpp"
#include "Matrix3.hpp"
#include "Quaternion.hpp"
#include "Vector3.hpp"
#include "SceneManager.hpp"
#include "Object.hpp"
#include "PerfTimer.hpp"

#include "components/TransformComponent.hpp"
#include "messages/AddComponentMessage.hpp"

using namespace Core;

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
    
    TransformComponent* transform = new TransformComponent(Vector3::Zero, Quaternion::Identity);
    
    AddComponentMessage addCompMsg(firstObj.GetID(), transform);
    bool handled = sceneMgr.SendMessage(&addCompMsg);
    
    // If the AddComponent message wasn't handled then the pointer never transferred
    // to the object and we need to take care of ourselves.
    if (!handled)
    {
        delete transform;
    }
    
    std::cout << firstObj.HasComponent(ComponentType::Transform) << std::endl;
}

void TestMath()
{
    // Creates a timer to time the cost of this entire function.
    // After the function goes out of scope the elapsed time is output to console.
    CreateFcnTimer;
    
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
    
    std::cout << "Rotated matrix (created manually): " << rotatedMatrix << std::endl;
    
    // Let's create the same matrix using FromEulerAngles now.
    rotatedMatrix = Matrix3::FromEulerAngles(0.f, Math::HalfPi, 0.f);
    
    std::cout << "Rotated matrix (from euler angles): " << rotatedMatrix << std::endl;
    
    std::cout << "Rotated matrix's forward: " << rotatedMatrix.GetRollAxis() << std::endl;
    
    quatFromMat.FromRotationMatrix(rotatedMatrix);
    
    std::cout << "Quaternion from rotated matrix: " << quatFromMat << std::endl;
    
    // Now we'll use Quaternion.FromAngleAxis to make the same quaternion.
    // This should rotate 90 degrees around the world Y axis just like we did
    // manually before.
    quatFromMat.FromAxisAngle(Vector3::Up, Math::HalfPi);
    
    std::cout << "Quaternion from FromAngleAxis: " << quatFromMat << std::endl;
    
    std::cout << "Quaternion from euler angles: " << Quaternion::FromEulerAngles(0.f, Math::HalfPi, 0.f) << std::endl;

    std::cout << "(Lerp) Same quaternion rotated back 35% of the way to identity: " << Quaternion::Lerp(quatFromMat, Quaternion::Identity, 0.35f) << std::endl;
    std::cout << "(Lerp) Same quaternion rotated back 70% of the way to identity: " << Quaternion::Lerp(quatFromMat, Quaternion::Identity, 0.70f) << std::endl;
    std::cout << "(Lerp) Same quaternion rotated back 90% of the way to identity: " << Quaternion::Lerp(quatFromMat, Quaternion::Identity, 0.9f) << std::endl << std::endl;

    std::cout << "(Nlerp) Same quaternion rotated back 35% of the way to identity: " << Quaternion::Nlerp(quatFromMat, Quaternion::Identity, 0.35f) << std::endl;
    std::cout << "(Nlerp) Same quaternion rotated back 70% of the way to identity: " << Quaternion::Nlerp(quatFromMat, Quaternion::Identity, 0.70f) << std::endl;
    std::cout << "(Nlerp) Same quaternion rotated back 90% of the way to identity: " << Quaternion::Nlerp(quatFromMat, Quaternion::Identity, 0.9f) << std::endl << std::endl;

    std::cout << "(Slerp) Same quaternion rotated back 35% of the way to identity: " << Quaternion::Slerp(quatFromMat, Quaternion::Identity, 0.35f) << std::endl;
    std::cout << "(Slerp) Same quaternion rotated back 70% of the way to identity: " << Quaternion::Slerp(quatFromMat, Quaternion::Identity, 0.70f) << std::endl;
    std::cout << "(Slerp) Same quaternion rotated back 90% of the way to identity: " << Quaternion::Slerp(quatFromMat, Quaternion::Identity, 0.9f) << std::endl << std::endl;
    
    // Test performance of various Quaternion lerping methods.
    {
        ScopeTimer("1000 Quaternion Lerps");
        for (int i = 0; i < 1000; ++i)
        {
            Quaternion::Lerp(quatFromMat, Quaternion::Identity, 0.35f);
        }
    }
    
    {
        ScopeTimer("1000 Quaternion Nlerps");
        for (int i = 0; i < 1000; ++i)
        {
            Quaternion::Nlerp(quatFromMat, Quaternion::Identity, 0.35f);
        }
    }
    
    {
        ScopeTimer("1000 Quaternion Slerps");
        for (int i = 0; i < 1000; ++i)
        {
            Quaternion::Slerp(quatFromMat, Quaternion::Identity, 0.35f);
        }
    }
    
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
    
    std::cout << "Matrix from the rotated Quaternion: " << Matrix3::FromQuaternion(quatFromMat) << std::endl;
    
    // And again we'll use Quaternion.FromAngleAxis to make the same quaternion.
    // This should rotate -90 degrees around the X axis.
    quatFromMat.FromAxisAngle(Vector3::Right, -Math::HalfPi);
    
    std::cout << "Quaternion from FromAngleAxis: " << quatFromMat << std::endl;
    
    std::cout << "Rotated matrix's transpose: " << rotatedMatrix.Transpose() << std::endl;
    
    Matrix3 rotatedInverse;
    if (!rotatedMatrix.Inverse(rotatedInverse))
    {
        throw "Failed to invert matrix";
    }
    
    std::cout << "Rotated matrix's inverse: " << rotatedInverse << std::endl;
    
    // Multiplying an inverse by the original should give a near-identity matrix
    std::cout << "Rotated * inverse (should equal identity) : " << rotatedMatrix * rotatedInverse << std::endl;
}

int main()
{
    TestSceneManager();
    
    std::cout << std::endl;
    
    TestMath();
    
    std::cout << std::endl;
    return 0;
}

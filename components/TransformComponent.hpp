#pragma once

#include "../core/Component.hpp"
#include "../math/Quaternion.hpp"
#include "../math/Vector3.hpp"

namespace Core
{
    class Object;
    class BaseMessage;
}

class TransformComponent : public Core::Component
{
public:
    TransformComponent(const Vector3& position, const Quaternion& rotation);
    
private:
    TransformComponent(const TransformComponent&);  // Prevent copying
    
    void MsgHandlerSetPosition(Core::BaseMessage* msg);
    void MsgHandlerGetPosition(Core::BaseMessage* msg);
    
private:
    Vector3 position;
    Quaternion rotation;
};

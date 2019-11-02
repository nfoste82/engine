#pragma once

#include "../core/BaseMessage.hpp"
#include "../math/Vector3.hpp"

using namespace Core;

class SetPositionMessage : public BaseMessage
{
public:
    SetPositionMessage(int targetObjectID, const Vector3& position) :
        BaseMessage(targetObjectID, MessageType::SetPosition),
        position(position)
    {
        
    }
    
    Vector3 position;
};

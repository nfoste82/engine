#pragma once

#include "../core/BaseMessage.hpp"
#include "../math/Quaternion.hpp"

using namespace Core;

class SetRotationMessage : public BaseMessage
{
public:
    SetRotationMessage(int targetObjectID, const Quaternion& rotation) :
        BaseMessage(targetObjectID, MessageType::SetRotation),
        rotation(rotation)
    {
    }
    
    Quaternion rotation;
};

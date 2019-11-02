#pragma once

#include "../core/BaseMessage.hpp"
#include "../math/Vector3.hpp"

using namespace Core;

class GetPositionMessage : public BaseMessage
{
public:
    GetPositionMessage(int targetObjectID) : BaseMessage(targetObjectID, MessageType::GetPosition)
    {
        
    }
    
    Vector3 position;
};

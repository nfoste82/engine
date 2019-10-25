#include "BaseMessage.hpp"

namespace Core
{
    BaseMessage::BaseMessage(int targetObjectID, MessageType messageType) :
        targetObjectID(targetObjectID),
        messageType(messageType)
    {
    }
}

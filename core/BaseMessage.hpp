#pragma once

enum class MessageType
{
    AddComponent = 0,
    GetPosition,
    SetPosition,
    GetRotation,
    SetRotation,
};

namespace Core
{
    class BaseMessage
    {
    public:
        int GetTargetObjectID() const { return targetObjectID; }
        MessageType GetType() const { return messageType; }
        
    protected:
        BaseMessage(int targetObjectID, MessageType messageType);
        
    private:
        int targetObjectID;
        MessageType messageType;
    };
}

#include "TransformComponent.hpp"

#include "../core/BaseMessage.hpp"
#include "../core/Object.hpp"
#include "../messages/SetPositionMessage.hpp"
#include "../messages/GetPositionMessage.hpp"

TransformComponent::TransformComponent(const Vector3& position, const Quaternion& rotation) :
    Component(Core::ComponentType::Transform),
    position(position),
    rotation(rotation)
{
    // TODO: Maybe a macro for message registration?
    {
        auto callback = std::bind(&TransformComponent::MsgHandlerSetPosition, this, std::placeholders::_1);
        RegisterMessage(MessageType::SetPosition, callback);
    }
    
    {
        auto callback = std::bind(&TransformComponent::MsgHandlerGetPosition, this, std::placeholders::_1);
        RegisterMessage(MessageType::GetPosition, callback);
    }
}

void TransformComponent::MsgHandlerSetPosition(Core::BaseMessage* msg)
{
    position = static_cast<SetPositionMessage*>(msg)->position;
}

void TransformComponent::MsgHandlerGetPosition(Core::BaseMessage* msg)
{
    static_cast<GetPositionMessage*>(msg)->position = position;
}

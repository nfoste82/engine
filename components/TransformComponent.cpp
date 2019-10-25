#include "TransformComponent.hpp"

TransformComponent::TransformComponent(const Vector3& position, const Quaternion& rotation) :
    Component(Core::ComponentType::Transform),
    position(position),
    rotation(rotation)
{
}

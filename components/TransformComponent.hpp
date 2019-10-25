#pragma once

#include "../core/Component.hpp"
#include "../math/Quaternion.hpp"
#include "../math/Vector3.hpp"

class TransformComponent : public Core::Component
{
public:
    TransformComponent(const Vector3& position, const Quaternion& rotation);
    
private:
    Vector3 position;
    Quaternion rotation;
};

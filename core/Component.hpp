#pragma once

namespace Core
{
    enum class ComponentType
    {
        Transform = 0
    };
    
    class Component
    {
    public:
        ComponentType GetComponentType() const { return componentType; }
        
    protected:
        Component(ComponentType componentType) :
            componentType(componentType)
        {
        }
        
    private:
        ComponentType componentType;
    };
}

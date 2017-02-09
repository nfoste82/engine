#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <vector>
#include "Component.h"

class Object
{
    public:

    Object(int uniqueID) :
        m_id(uniqueID)
    {

    }

    int32_t GetID() const { return m_id; }

    private:

    int32_t m_id;
    std::vector<std::shared_ptr<Core::Component>> m_components;
};

#endif //OBJECT_H
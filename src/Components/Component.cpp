#include "Components/Component.hpp"

#include <stdexcept>

bool Component::init(int ownerID)
{
    m_ownerID = ownerID;

    return onInit(ownerID);
}

int Component::getOwnerID()
{
    if (m_ownerID == -1)
    {
        throw std::runtime_error("Component not set to entity!");
    }

    return m_ownerID;
}

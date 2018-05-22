#include "Components/Component.hpp"

#include <stdexcept>

bool Component::init(Entity* owner)
{
    m_owner = owner;

    return onInit(owner);
}

Entity& Component::getOwner()
{
    if (m_owner == nullptr)
    {
        throw std::runtime_error("WHAT THE FUCK!");
    }

    return *m_owner;
}

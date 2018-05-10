#include "Components/Component.hpp"

bool Component::init(Entity& owner)
{
    m_owner = &owner;

    return onInit(owner);
}

Entity* const Component::getOwner()
{
    return m_owner;
}

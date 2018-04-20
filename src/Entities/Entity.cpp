#include "Entities/Entity.hpp"

void Entity::addComponent(std::unique_ptr<Component>& component)
{
    m_components.push_back(std::move(component));
}

Component& Entity::getComponentByType(int type)
{
    for (auto& comp : m_components)
    {
        if (comp->type == type)
        {
            return *comp;
        }
    }

    throw std::logic_error("Component does not exist");
}

bool Entity::init()
{
    for (auto& comp : m_components)
    {
        if (!comp->init(*this))
        {
            return false;
        }
    }

    return true;
}

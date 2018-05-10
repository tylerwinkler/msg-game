#include "Entities/Entity.hpp"

void Entity::addComponent(std::unique_ptr<Component> component)
{
    m_components.insert(std::make_pair(component->type, std::move(component)));
}

Component& Entity::getComponentByType(int type)
{
    if (m_components.count(type) != 0)
    {
        return *m_components.at(type);
    }

    throw std::logic_error("Component does not exist");
}

bool Entity::init()
{
    for (auto& comp : m_components)
    {
        if (!comp.second->init(*this))
        {
            return false;
        }
    }

    return true;
}

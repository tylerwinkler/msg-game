#include "Entities/Entity.hpp"

#include "Components/SpriteComponent.hpp"

void Entity::setPosition(int x, int y)
{
    oldPosition.x = position.x;
    oldPosition.y = position.y;

    position.x = x;
    position.y = y;

    for (auto observer : m_positionObservers)
    {
        observer->receive(x, y);
    }
}

void Entity::assignID(int id)
{
    this->id = id;
}

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
        if (!comp.second->init(id))
        {
            return false;
        }
    }

    return true;
}

void Entity::addObserver(Component* component)
{
    m_positionObservers.push_back(component);
}

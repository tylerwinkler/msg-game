#ifndef MSG_GAME_ENTITY_HPP
#define MSG_GAME_ENTITY_HPP

#include <map>
#include <memory>
#include <vector>

#include "SFML/System/Vector2.hpp"

#include "Components/Component.hpp"

class Entity
{
public:
    void setPosition(int x, int y);

    sf::Vector2f position;

    int id;

    void assignID(int id);

    void addComponent(std::unique_ptr<Component> component);

    Component& getComponentByType(int type);

    template <class T>
    T& getComponent();

    template <class T>
    bool hasComponent(T obj);

    bool init();

    void addObserver(Component* component);

private:
    std::map<int, std::unique_ptr<Component>> m_components;

    std::vector<Component*> m_positionObservers;
};

template <class T>
T& Entity::getComponent()
{
    T obj;
    return dynamic_cast<T&>(getComponentByType(obj.type));
}

template <class T>
bool Entity::hasComponent(T obj)
{
    return m_components.count(obj.type) != 0;
}

#endif // MSG_GAME_ENTITY_HPP

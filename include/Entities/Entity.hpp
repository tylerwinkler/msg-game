#ifndef MSG_GAME_ENTITY_HPP
#define MSG_GAME_ENTITY_HPP

#include <map>
#include <memory>

#include "SFML/System/Vector2.hpp"

#include "Components/Component.hpp"

class Entity
{
public:
    sf::Vector2f position;

    void addComponent(std::unique_ptr<Component> component);

    Component& getComponentByType(int type);

    template <class T>
    T& getComponent();

    bool init();

private:
    std::map<int, std::unique_ptr<Component>> m_components;
};

template <class T>
T& Entity::getComponent()
{
    T obj;
    return dynamic_cast<T&>(getComponentByType(obj.type));

//    for (auto& comp : m_components)
//    {
//        if (dynamic_cast<T*>(comp.second.get()) != nullptr)
//        {
//            return dynamic_cast<T&>(*comp.second);
//        }
//    }
//
//    throw std::logic_error("Component does not exist");
}

#endif // MSG_GAME_ENTITY_HPP

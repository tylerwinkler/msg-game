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

    bool init();

private:
    std::map<int, std::unique_ptr<Component>> m_components;
};

#endif // MSG_GAME_ENTITY_HPP

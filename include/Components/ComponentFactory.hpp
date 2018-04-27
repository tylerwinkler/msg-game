#ifndef MSG_GAME_COMPONENTS_COMPONENTFACTORY_HPP
#define MSG_GAME_COMPONENTS_COMPONENTFACTORY_HPP

#include <memory>

#include "Components/Component.hpp"

class ComponentFactory
{
public:
    typedef std::unique_ptr<Component> ComponentPtr;

public:
    static ComponentPtr createAnimationComponent();

    static ComponentPtr createCollisionComponent();

    static ComponentPtr createHealthComponent();

    static ComponentPtr createSpriteComponent();
}; // ComponentFactory

#endif // MSG_GAME_COMPONENTS_COMPONENTFACTORY_HPP

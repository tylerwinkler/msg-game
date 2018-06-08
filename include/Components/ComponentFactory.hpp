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
    static ComponentPtr createCollisionComponent(int x, int y, int width, int height);

    static ComponentPtr createDialogComponent();

    static ComponentPtr createHealthComponent();

    static ComponentPtr createInteractionComponent();

    static ComponentPtr createLootComponent();

    static ComponentPtr createSpriteComponent();
    static ComponentPtr createSpriteComponent(const std::string& texture);
}; // ComponentFactory

#endif // MSG_GAME_COMPONENTS_COMPONENTFACTORY_HPP

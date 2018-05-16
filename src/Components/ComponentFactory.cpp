#include "Components/ComponentFactory.hpp"

#include "Components/AnimationComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/InteractionComponent.hpp"
#include "Components/LootComponent.hpp"
#include "Components/SpriteComponent.hpp"

ComponentFactory::ComponentPtr ComponentFactory::createAnimationComponent()
{
    std::unique_ptr<Component> component(new AnimationComponent());

    return std::move(component);
}

ComponentFactory::ComponentPtr ComponentFactory::createCollisionComponent()
{
    std::unique_ptr<Component> component(new CollisionComponent());

    return std::move(component);
}

ComponentFactory::ComponentPtr ComponentFactory::createCollisionComponent(int x, int y, int width, int height)
{
    std::unique_ptr<Component> component(new CollisionComponent(x, y, width, height));

    return std::move(component);
}

ComponentFactory::ComponentPtr ComponentFactory::createHealthComponent()
{
    std::unique_ptr<Component> component(new HealthComponent());

    return std::move(component);
}

ComponentFactory::ComponentPtr ComponentFactory::createInteractionComponent()
{
    std::unique_ptr<Component> component(new InteractionComponent());

    return std::move(component);
}

ComponentFactory::ComponentPtr ComponentFactory::createLootComponent()
{
    std::unique_ptr<Component> component(new LootComponent());

    return std::move(component);
}

ComponentFactory::ComponentPtr ComponentFactory::createSpriteComponent()
{
    std::unique_ptr<Component> component(new SpriteComponent());

    return std::move(component);
}

ComponentFactory::ComponentPtr ComponentFactory::createSpriteComponent(const std::string& texture)
{
    std::unique_ptr<Component> component(new SpriteComponent(texture));

    return std::move(component);
}

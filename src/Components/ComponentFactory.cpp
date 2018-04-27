#include "Components/ComponentFactory.hpp"

#include "Components/AnimationComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/SpriteComponent.hpp"

ComponentFactory::ComponentPtr ComponentFactory::createAnimationComponent()
{
    std::unique_ptr<Component> component(new AnimationComponent());

    return std::move(component);
}

ComponentFactory::ComponentPtr ComponentFactory::createCollisionComponent()
{
    std::unique_ptr<Component> component(new CollisionComponent(200, 200, 1000, 1000));

    return std::move(component);
}

ComponentFactory::ComponentPtr ComponentFactory::createHealthComponent()
{

}

ComponentFactory::ComponentPtr ComponentFactory::createSpriteComponent()
{
    std::unique_ptr<Component> component(new SpriteComponent());

    return std::move(component);
}

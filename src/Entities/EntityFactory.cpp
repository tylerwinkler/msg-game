#include "Entities/EntityFactory.hpp"

#include "Components/CollisionComponent.hpp"

#include "Components/ComponentFactory.hpp"

Entity EntityFactory::createMapTransition(int transitionId)
{
    Entity entity;

    entity.addComponent(ComponentFactory::createCollisionComponent(-24, -24, 48, 48));

    Component& comp = entity.getComponentByType(ComponentType::CollisionComponent);

    CollisionComponent& coll = dynamic_cast<CollisionComponent&>(comp);

    coll.setCollisionFunc([]{
                              throw std::logic_error("Not implemented");
                          });

    if (!entity.init())
    {
        throw std::logic_error("Failed to init Map Transition Entity");
    }

    return entity;
}

Entity EntityFactory::createCharacter(int characterId)
{
    Entity entity;

    entity.addComponent(ComponentFactory::createAnimationComponent());
    entity.addComponent(ComponentFactory::createCollisionComponent());
    entity.addComponent(ComponentFactory::createHealthComponent());
    entity.addComponent(ComponentFactory::createSpriteComponent());

    if (!entity.init())
    {
        throw std::logic_error("Failed to init Character Entity");
    }

    return entity;
}

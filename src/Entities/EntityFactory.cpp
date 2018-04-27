#include "Entities/EntityFactory.hpp"

#include "Components/CollisionComponent.hpp"

#include "Components/ComponentFactory.hpp"

Entity EntityFactory::createMapTransition(int transitionId)
{
    Entity entity;

    entity.addComponent(ComponentFactory::createCollisionComponent());

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

#include "Components/SpriteComponent.hpp"

#include "Entities/Entity.hpp"

SpriteComponent::SpriteComponent()
{
    type = ComponentType::SpriteComponent;
}

bool SpriteComponent::init(Entity& owner)
{
    return true;
}

void SpriteComponent::update(Entity& owner)
{

}

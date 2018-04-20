#include "Components/SpriteComponent.hpp"

#include "Entity.hpp"

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

#include "Components/AnimationComponent.hpp"

#include "Entities/Entity.hpp"

AnimationComponent::AnimationComponent()
{
    type = ComponentType::AnimationComponent;
}

bool AnimationComponent::init(Entity& owner)
{
    try
    {
        m_spriteComponent = dynamic_cast<SpriteComponent*>(&owner.getComponentByType(ComponentType::SpriteComponent));
    } catch (...)
    {
        throw std::logic_error("Component missing. failed to init");
    }

    return true;
}

void AnimationComponent::update(Entity& owner)
{

}

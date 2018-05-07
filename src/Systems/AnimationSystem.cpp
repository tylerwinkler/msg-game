#include "Systems/AnimationSystem.hpp"

#include "Components/AnimationComponent.hpp"

void AnimationSystem::update(sf::Time& t)
{

}

void AnimationSystem::addComponent(AnimationComponent* component)
{
    m_animations.push_back(component);
}

void AnimationSystem::removeComponent(AnimationComponent* component)
{
    m_animations.erase(std::remove(m_animations.begin(), m_animations.end(), component), m_animations.end());
}

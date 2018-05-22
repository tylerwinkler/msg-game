#include "Systems/AnimationSystem.hpp"

#include "Components/AnimationComponent.hpp"

#include <iostream>

void AnimationSystem::update(float time)
{
    int i = 0;
    for (auto animation : m_animations)
    {
        // std::cout << "Updating animation #" << ++i << "\n";
        animation->update(time);
    }
    // std::cout << "\n";
}

void AnimationSystem::addComponent(AnimationComponent* component)
{
    m_animations.push_back(component);
}

void AnimationSystem::removeComponent(AnimationComponent* component)
{
    m_animations.erase(std::remove(m_animations.begin(), m_animations.end(), component), m_animations.end());
}

#include "Components/AnimationComponent.hpp"

#include "Entities/Entity.hpp"

AnimationComponent::AnimationComponent()
{
    type = ComponentType::AnimationComponent;

    m_currentAnimation = nullptr;
}

bool AnimationComponent::onInit(Entity* owner)
{
    try
    {
        m_spriteComponent = &owner->getComponent<SpriteComponent>();
    } catch (...)
    {
        throw std::logic_error("Component missing. failed to init");
    }

    return true;
}

void AnimationComponent::addAnimation(const std::string& name, Animation animation)
{
    m_animations.insert(std::make_pair(name, animation));
}

void AnimationComponent::playAnimation(const std::string& animationName)
{
    if (m_animations.count(animationName) == 0)
    {
        throw std::logic_error("Animation does not exist");
    }

    m_currentAnimation = &m_animations.at(animationName);
    m_spriteComponent->setRect(m_currentAnimation->frames.front());

    m_accumulatedTime = 0.f;
    m_currentIndex = 0;

    m_animationMultiplier = 10.f;

    m_playing = true;
}

void AnimationComponent::pauseAnimation()
{
    m_playing = false;
}

void AnimationComponent::update(float time)
{
    if (m_currentAnimation == nullptr || !m_playing)
    {
        return;
    }

    m_accumulatedTime += time;

    if (m_accumulatedTime >= m_currentAnimation->animationTime / m_animationMultiplier)
    {
        m_accumulatedTime -= m_currentAnimation->animationTime / m_animationMultiplier;
        m_currentIndex += 1;

        if (m_currentIndex >= m_currentAnimation->frames.size())
        {
            m_currentIndex = 0;
        }

        m_spriteComponent->setRect(m_currentAnimation->frames[m_currentIndex]);
    }
}

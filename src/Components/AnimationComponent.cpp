#include "Components/AnimationComponent.hpp"

#include "Entities/Entity.hpp"

#include "Systems/EntitySystem.hpp"

#include "GameEngine.hpp"
#include "Global.hpp"

AnimationComponent::AnimationComponent()
{
    type = ComponentType::AnimationComponent;

    m_currentAnimation = nullptr;
}

bool AnimationComponent::onInit(int ownerID)
{
    try
    {
        m_spriteComponent = &Global::game.getEntitySystem().getEntity(getOwnerID()).getComponent<SpriteComponent>();
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

    m_playing = true;

    // Animation already playing
    if (m_animation == animationName)
    {
        return;
    }

    m_animation = animationName;

    m_currentAnimation = &m_animations.at(animationName);
    m_spriteComponent->setRect(m_currentAnimation->frames.front());

    m_accumulatedTime = 0.f;
    m_currentIndex = 0;

    m_animationMultiplier = 10.f;
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

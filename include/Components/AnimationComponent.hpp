#ifndef MSG_GAME_COMPONENTS_ANIMATIONCOMPONENT_HPP
#define MSG_GAME_COMPONENTS_ANIMATIONCOMPONENT_HPP

#include <map>

#include "Animation.hpp"

#include "Component.hpp"
#include "SpriteComponent.hpp"

class AnimationComponent : public Component
{
friend class AnimationSystem;

public:
    AnimationComponent();

public:
    bool onInit(Entity& owner) final override;

    void addAnimation(const std::string& name, Animation animation);

    void playAnimation(const std::string& animationName);

    void pauseAnimation();

private:
    void update(float time);

private:
    std::map<std::string, Animation> m_animations;
    Animation* m_currentAnimation;

    float m_accumulatedTime;
    int m_currentIndex;

    float m_animationMultiplier;

    bool m_playing;

    SpriteComponent* m_spriteComponent;
};

#endif // MSG_GAME_COMPONENTS_ANIMATIONCOMPONENT_HPP

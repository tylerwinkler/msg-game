#ifndef MSG_GAME_SYSTEMS_ANIMATIONSYSTEM_HPP
#define MSG_GAME_SYSTEMS_ANIMATIONSYSTEM_HPP

#include <vector>

class AnimationComponent;
namespace sf { class Time; }

class AnimationSystem
{
public:
    void update(float time);

    void addComponent(AnimationComponent* component);

    void removeComponent(AnimationComponent* component);

private:
    std::vector<AnimationComponent*> m_animations;
}; // AnimationSystem

#endif // MSG_GAME_SYSTEMS_ANIMATIONSYSTEM_HPP

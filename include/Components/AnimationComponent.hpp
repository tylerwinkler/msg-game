#ifndef MSG_GAME_COMPONENTS_ANIMATIONCOMPONENT_HPP
#define MSG_GAME_COMPONENTS_ANIMATIONCOMPONENT_HPP

#include "Component.hpp"
#include "SpriteComponent.hpp"

class AnimationComponent : public Component
{
public:
    friend class AnimationSystem;

public:
    AnimationComponent();

public:
    bool init(Entity& owner);

    void update(Entity& owner);

private:
    SpriteComponent*    m_spriteComponent;
};

#endif // MSG_GAME_COMPONENTS_ANIMATIONCOMPONENT_HPP

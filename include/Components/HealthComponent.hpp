#ifndef MSG_GAME_COMPONENTS_HEALTHCOMPONENT_HPP
#define MSG_GAME_COMPONENTS_HEALTHCOMPONENT_HPP

#include "Component.hpp"

class HealthComponent : public Component
{
public:
    HealthComponent();

    float hp;

public:
    bool init(Entity& owner);

    void update(Entity& owner);
};

#endif // MSG_GAME_COMPONENTS_HEALTHCOMPONENT_HPP

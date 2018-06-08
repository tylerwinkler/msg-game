#ifndef MSG_GAME_COMPONENTS_HEALTHCOMPONENT_HPP
#define MSG_GAME_COMPONENTS_HEALTHCOMPONENT_HPP

#include "Component.hpp"

class HealthComponent : public Component
{
public:
    HealthComponent();

    float hp;

public:
    void update(int ownerID);
};

#endif // MSG_GAME_COMPONENTS_HEALTHCOMPONENT_HPP

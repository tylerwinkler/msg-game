#ifndef MSG_GAME_COMPONENTS_INTERACTIONCOMPONENT_HPP
#define MSG_GAME_COMPONENTS_INTERACTIONCOMPONENT_HPP

#include <functional>

#include "Components/Component.hpp"

class InteractionComponent : public Component
{
public:
    InteractionComponent();

    void setInteractionFunction(std::function<void()> func);

    void onInteract();

private:
    std::function<void()> m_interactFunction;
}; // InteractionComponent

#endif // MSG_GAME_COMPONENTS_INTERACTIONCOMPONENT_HPP

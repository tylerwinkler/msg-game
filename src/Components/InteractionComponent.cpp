#include "Components/InteractionComponent.hpp"

InteractionComponent::InteractionComponent() : m_interactFunction(nullptr)
{
    type = ComponentType::InteractionComponent;
}

void InteractionComponent::setInteractionFunction(std::function<void()> func)
{
    m_interactFunction = std::move(func);
}

void InteractionComponent::onInteract()
{
    if (m_interactFunction != nullptr)
    {
        m_interactFunction();
    }
}

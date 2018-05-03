#include "Components/HealthComponent.hpp"

HealthComponent::HealthComponent()
{
    type = ComponentType::HealthComponent;

    hp = 1.f;
}

bool HealthComponent::init(Entity& owner)
{
    return true;
}

void HealthComponent::update(Entity& owner)
{

}


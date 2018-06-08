#include "Components/HealthComponent.hpp"

HealthComponent::HealthComponent()
{
    type = ComponentType::HealthComponent;

    hp = 1.f;
}

void HealthComponent::update(int ownerID)
{

}


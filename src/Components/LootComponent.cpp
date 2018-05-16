#include "Components/LootComponent.hpp"

LootComponent::LootComponent()
{
    type = ComponentType::LootComponent;
}

std::vector<int>& LootComponent::getItems()
{
    return m_items;
}


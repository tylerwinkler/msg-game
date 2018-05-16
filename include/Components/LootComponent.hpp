#ifndef MSG_GAME_COMPONENTS_LOOTCOMPONENT_HPP
#define MSG_GAME_COMPONENTS_LOOTCOMPONENT_HPP

#include <vector>

#include "Components/Component.hpp"

class LootComponent : public Component
{
public:
    LootComponent();

    std::vector<int>& getItems();

private:
    std::vector<int> m_items;
};

#endif // MSG_GAME_COMPONENTS_LOOTCOMPONENT_HPP

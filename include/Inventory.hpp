#ifndef MSG_GAME_INVENTORY_HPP
#define MSG_GAME_INVENTORY_HPP

#include <vector>

#include "Item.hpp"

class Inventory
{
public:
    void addItem(std::string item);
    std::string getItemInSlot(int i);

    int getSize();

private:
    std::vector<std::string> m_items;
}; // Inventory

#endif // MSG_GAME_INVENTORY_HPP

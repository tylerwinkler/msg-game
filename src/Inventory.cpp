#include "Inventory.hpp"

void Inventory::addItem(std::string item)
{
    m_items.push_back(item);
}

std::string Inventory::getItemInSlot(int i)
{
    return m_items[i];
}

int Inventory::getSize()
{
    return m_items.size();
}

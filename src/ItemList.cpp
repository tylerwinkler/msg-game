#include "ItemList.hpp"

std::vector<Item> ItemList::m_items;

ItemNotFoundException::ItemNotFoundException(const std::string& message) : std::logic_error(message)
{
}

ItemList::ItemList()
{
    m_items.resize(256);

    Item devKnife;
    devKnife.m_id = getEmptySlot();
    devKnife.m_name = "Developer's Knife";
    devKnife.m_type = ItemType::Weapon;
    devKnife.m_subType = ItemSubType::Sword;
    devKnife.m_data.weapon.minDmg = 24;
    devKnife.m_data.weapon.maxDmg = 42;
    devKnife.m_data.weapon.fireRate = 1.3;

    addItem(devKnife);

    devKnife.m_id = getEmptySlot();
    addItem(devKnife);
}

const Item& ItemList::getItemById(int id)
{
    return m_items[id];
}

const Item& ItemList::getItemByName(const std::string& name)
{
    for (const Item& item : m_items)
    {
        if (item.m_name == name)
        {
            return item;
        }
    }

    throw ItemNotFoundException(name + " could not be found");
}

int ItemList::getEmptySlot()
{
    for (int i = 0; i < m_items.size(); ++i)
    {
        if (m_items[i].m_id == -1)
        {
            return i;
        }
    }

    return m_items.size();
}

const std::vector<Item>& ItemList::getItems()
{
    return m_items;
}

void ItemList::addItem(Item& item)
{
    while (m_items.size() <= item.m_id)
    {
        m_items.resize(m_items.size() * 2);
    }

    m_items[item.m_id] = item;
}

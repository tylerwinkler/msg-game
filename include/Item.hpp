#ifndef MSG_GAME_ITEM_HPP
#define MSG_GAME_ITEM_HPP

#include <string>

enum ItemType
{
    Weapon,
    Armor,
    Jewelry,
    Consumable,
}; // ItemType

enum ItemSubType
{
    Sword,
    Helmet,
    Chest,
    Legs,
    Gloves,
    Boots
}; // ItemSubType

struct WeaponData
{
    int minDmg;
    int maxDmg;
    float fireRate;
}; // WeaponData

struct ArmorData
{
    int armor;
}; // ArmorData

struct JewelryData
{

}; // JewelryData

struct ConsumableData
{

}; //ConsumableData

union ItemData
{
    WeaponData weapon;
    ArmorData armor;
    JewelryData jewelry;
    ConsumableData consumable;
};

class Item
{
public:
    Item();

public:
    int m_id;
    std::string m_name;

    ItemData m_data;

    ItemType m_type;
    ItemSubType m_subType;

    int m_inventoryStackLimit;
    int m_bankStackLimit;
}; // Item

#endif // MSG_GAME_ITEM_HPP

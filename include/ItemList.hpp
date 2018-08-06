#ifndef MSG_GAME_ITEMLIST_HPP
#define MSG_GAME_ITEMLIST_HPP

#include <stdexcept>
#include <vector>

#include "Item.hpp"

class ItemNotFoundException : public std::logic_error
{
public:
    ItemNotFoundException(const std::string& message);
};

class ItemList
{
public:
    // Populates the ItemList with a default set of developer items.
    ItemList();

public:
    /* getItemById returns the item occupying the item vector at the index given by id.
    // This is a fast operation.
    // Throws ItemNotFoundException when a matching id does not exist.
    */
    const static Item& getItemById(int id);

    /* getItemByName performs an item by item lookup for an item matching the given name
    // This can be a slow operation.
    // Throws ItemNotFoundException when a matching name cant be found.
    */
    const static Item& getItemByName(const std::string& name);

    // Returns the next available item id
    static int getEmptySlot();

    const static std::vector<Item>& getItems();

private:
    static void addItem(Item& item);

private:
    static std::vector<Item> m_items;


};

#endif // MSG_GAME_ITEMLIST_HPP

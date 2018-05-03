#include "Player.hpp"

Inventory& Player::getInventory()
{
    return m_inventory;
}

Wallet& Player::getWallet()
{
    return m_wallet;
}

Entity& Player::getCharacter()
{
    return m_character;
}

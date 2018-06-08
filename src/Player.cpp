#include "Player.hpp"

Inventory& Player::getInventory()
{
    return m_inventory;
}

Wallet& Player::getWallet()
{
    return m_wallet;
}

void Player::setCharacterID(int id)
{
    m_characterID = id;
}

int Player::getCharacterID()
{
    return m_characterID;
}

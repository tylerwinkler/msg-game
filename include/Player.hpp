#ifndef MSG_GAME_PLAYER_HPP
#define MSG_GAME_PLAYER_HPP

#include "Entities/Entity.hpp"

#include "Inventory.hpp"
#include "Wallet.hpp"

class Player
{
public:
    Inventory& getInventory();

    Wallet& getWallet();

    void setCharacterID(int id);

    int getCharacterID();

private:
    Inventory m_inventory;

    Wallet m_wallet;

    int m_characterID;
}; // Player

#endif // MSG_GAME_PLAYER_HPP

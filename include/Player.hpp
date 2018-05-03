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

    Entity& getCharacter();

private:
    Inventory m_inventory;

    Wallet m_wallet;

    Entity m_character;
}; // Player

#endif // MSG_GAME_PLAYER_HPP

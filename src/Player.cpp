#include "Player.hpp"

int Player::getGold()
{
    return m_gold;
}

void Player::setGold(int gold)
{
    m_gold = gold;
}

void Player::addGold(int gold)
{
    m_gold += gold;
}

void Player::removeGold(int gold)
{
    m_gold -= gold;
}

bool Player::hasGold(int gold)
{
    return m_gold >= gold;
}

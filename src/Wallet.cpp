#include "Wallet.hpp"

Wallet::Wallet() : m_gold(0)
{
}

int Wallet::getGold()
{
    return m_gold;
}

void Wallet::setGold(int gold)
{
    m_gold = gold;
}

void Wallet::addGold(int gold)
{
    m_gold += gold;
}

void Wallet::removeGold(int gold)
{
    m_gold -= gold;
}

bool Wallet::hasGold(int gold)
{
    return m_gold >= gold;
}


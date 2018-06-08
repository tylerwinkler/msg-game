#include "Wallet.hpp"

namespace
{
    const int MaxCurrency = 1'000'000'000;
}

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

    if (m_gold > MaxCurrency)
    {
        m_gold = MaxCurrency;
    }
}

void Wallet::addGold(int gold)
{
    m_gold += gold;

    if (m_gold > MaxCurrency)
    {
        m_gold = MaxCurrency;
    }
}

void Wallet::removeGold(int gold)
{
    m_gold -= gold;

    if (m_gold < 0)
    {
        m_gold = 0;
    }
}

bool Wallet::hasGold(int gold)
{
    return m_gold >= gold;
}


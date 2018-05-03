#ifndef MSG_GAME_WALLET_HPP
#define MSG_GAME_WALLET_HPP

class Wallet
{
public:
    int getGold();

    void setGold(int gold);

    void addGold(int gold);

    void removeGold(int gold);

    bool hasGold(int gold);

private:
    int m_gold;
}; // Wallet

#endif // MSG_GAME_WALLET_HPP

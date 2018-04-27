#ifndef MSG_GAME_PLAYER_HPP
#define MSG_GAME_PLAYER_HPP

class Player
{
public:
    int getGold();
    void setGold(int gold);
    void addGold(int gold);
    void removeGold(int gold);
    bool hasGold(int gold);

private:
    int m_gold;
}; // Player

#endif // MSG_GAME_PLAYER_HPP

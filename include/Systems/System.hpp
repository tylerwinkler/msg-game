#ifndef MSG_GAME_SYSTEMS_SYSTEM_HPP
#define MSG_GAME_SYSTEMS_SYSTEM_HPP

class GameEngine;

class System
{
public:
    System(GameEngine& engine);

    virtual ~System();

protected:
    GameEngine& getEngine();

private:
    GameEngine& m_engine;
};

#endif // MSG_GAME_SYSTEMS_SYSTEM_HPP

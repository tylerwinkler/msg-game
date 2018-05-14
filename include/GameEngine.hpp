#ifndef MSG_GAME_GAMEENGINE_HPP
#define MSG_GAME_GAMEENGINE_HPP

#include "SFML/Graphics/RenderWindow.hpp"

class State;
class StateMachine;
class TextureManager;

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

public:
    void run(State* initialState);

    void quit();

    StateMachine& getStateMachine();

    TextureManager& getTextureManager();

    sf::RenderWindow& getWindow();

private:
    bool m_running;

    sf::RenderWindow m_window;

    StateMachine* m_stateMachine;

    TextureManager* m_textureManager;
}; // GameEngine

#endif // MSG_GAME_GAMEENGINE_HPP

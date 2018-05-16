#ifndef MSG_GAME_GAMEENGINE_HPP
#define MSG_GAME_GAMEENGINE_HPP

#include "SFML/Graphics/RenderWindow.hpp"

class FontManager;
class State;
class StateMachine;
class TextureManager;

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

public:
    void run(State* initialState, int ups = 25);

    void quit();

    FontManager& getFontManager();

    StateMachine& getStateMachine();

    TextureManager& getTextureManager();

    sf::RenderWindow& getWindow();

private:
    bool m_running;

    FontManager* m_fontManager;

    sf::RenderWindow m_window;

    StateMachine* m_stateMachine;

    TextureManager* m_textureManager;
}; // GameEngine

#endif // MSG_GAME_GAMEENGINE_HPP

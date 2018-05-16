#ifndef MSG_GAME_MAINMENUSTATE_HPP
#define MSG_GAME_MAINMENUSTATE_HPP

#include "SFML/Graphics/Text.hpp"

#include "State.hpp"

class MainMenuState : public State
{
public:
    bool init() final override;

    void onMouseButton(int x, int y, int button, bool pressed) final override;

    void onKey(int keyCode, bool control, bool alt, bool shift, bool system, bool pressed) final override;

    void update() final override;

    void render() final override;

private:
    sf::Text m_text;
    sf::Text m_text1;
    sf::Text m_text2;
    sf::Text m_text3;
}; // MainMenuState

#endif // MSG_GAME_MAINMENUSTATE_HPP

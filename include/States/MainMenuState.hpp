#ifndef MSG_GAME_MAINMENUSTATE_HPP
#define MSG_GAME_MAINMENUSTATE_HPP

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

#include "State.hpp"

class MainMenuState : public State
{
public:
    bool init() final override;

    void onMouseButton(int x, int y, int button, bool pressed) final override;

    void onKey(int keyCode, bool control, bool alt, bool shift, bool system, bool pressed) final override;

    void update() final override;

    void render(float interpolation) final override;

private:
    sf::Sprite m_background;
    sf::Text m_menuHeader;
    sf::Text m_newGameText;
    sf::Text m_loadGameText;
    sf::Text m_optionsText;
    sf::Text m_exitText;
}; // MainMenuState

#endif // MSG_GAME_MAINMENUSTATE_HPP

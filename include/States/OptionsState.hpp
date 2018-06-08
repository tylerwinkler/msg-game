#ifndef MSG_GAME_OPTIONSSTATE_HPP
#define MSG_GAME_OPTIONSSTATE_HPP

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

#include "State.hpp"

class OptionsState : public State
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
    sf::Text m_backText;
}; // OptionsState

#endif // MSG_GAME_OPTIONSSTATE_HPP

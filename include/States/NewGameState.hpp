#ifndef MSG_GAME_NEWGAMETATE_HPP
#define MSG_GAME_NEWGAMETATE_HPP

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

#include "State.hpp"

class NewGameState : public State
{
public:
    bool init() final override;

    void onMouseButton(int x, int y, int button, bool pressed) final override;

    void onKey(int keyCode, bool control, bool alt, bool shift, bool system, bool pressed) final override;

    void update() final override;

    void render() final override;

private:
    sf::Sprite m_background;
    sf::Text m_menuHeader;
    sf::Text m_backText;
}; // NewGameState

#endif // MSG_GAME_NEWGAMETATE_HPP


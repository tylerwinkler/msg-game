#ifndef MSG_GAME_MAINMENUSTATE_HPP
#define MSG_GAME_MAINMENUSTATE_HPP

#include "State.hpp"

class MainMenuState : public State
{
public:
    void handleEvent(sf::Event event) final override;

    void update() final override;

    void render() final override;
}; // MainMenuState

#endif // MSG_GAME_MAINMENUSTATE_HPP

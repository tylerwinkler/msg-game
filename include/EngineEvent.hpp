#ifndef MSG_GAME_ENGINEEVENT_HPP
#define MSG_GAME_ENGINEEVENT_HPP

#include "SFML/Window/Event.hpp"

struct EngineEvent
{
    bool handled = false;
    sf::Event event;
};

#endif // MSG_GAME_ENGINEEVENT_HPP

#ifndef MSG_GAME_STATE_HPP
#define MSG_GAME_STATE_HPP

#include "SFML/Window/Event.hpp"

class State
{
public:
    virtual bool init(){return true;}

    virtual void handleEvent(sf::Event event){}

    virtual void update(){}

    virtual void render(){}

    virtual void cleanup(){}
}; // State

#endif // MSG_GAME_STATE_HPP

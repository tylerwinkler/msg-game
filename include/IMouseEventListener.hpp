#ifndef MSG_GAME_IMOUSEEVENTLISTENER_HPP
#define MSG_GAME_IMOUSEEVENTLISTENER_HPP

#include "SFML/Window/Mouse.hpp"

class IMouseEventListener
{
public:
    virtual void onMouseButton(int x, int y, sf::Mouse::Button button, bool pressed);
}; // IMouseEventListener

#endif // MSG_GAME_IMOUSEEVENTLISTENER_HPP

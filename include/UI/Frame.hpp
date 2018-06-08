#ifndef MSG_GAME_UI_FRAME_HPP
#define MSG_GAME_UI_FRAME_HPP

#include "SFML/Graphics/RenderTarget.hpp"

class Frame
{
public:
    Frame();

public:
    void open();

    void close();

    bool isOpen();

    void render(sf::RenderTarget& target);

private:
    virtual void onRender(sf::RenderTarget& target);

private:
    bool m_open;
}; // Frame

#endif // MSG_GAME_UI_FRAME_HPP

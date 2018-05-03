#ifndef MSG_GAME_TILEMAP_TILEMAPEDITOR_HPP
#define MSG_GAME_TILEMAP_TILEMAPEDITOR_HPP

#include "IMouseEventListener.hpp"

class TilemapEditor : public IMouseEventListener
{
public:
    void onMouseButton(int x, int y, sf::Mouse::Button button, bool pressed) final;
};

#endif // MSG_GAME_TILEMAP_TILEMAPEDITOR_HPP

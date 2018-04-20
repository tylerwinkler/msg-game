#ifndef MSG_GAME_IRENDERER_HPP
#define MSG_GAME_IRENDERER_HPP

class Tile;

class IRenderer
{
public:
    virtual void renderTile(Tile& tile){}
};

#endif // MSG_GAME_IRENDERER_HPP

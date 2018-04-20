#ifndef MSG_GAME_SFMLRENDERER_HPP
#define MSG_GAME_SFMLRENDERER_HPP

#include "Tile.hpp"

class SFMLRenderer : public IRenderer
{
public:
    void renderTile(Tile& tile);
};

#endif // MSG_GAME_SFMLRENDERER_HPP

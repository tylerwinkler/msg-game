#ifndef MSG_GAME_TILERENDERER_HPP
#define MSG_GAME_TILERENDERER_HPP

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "TileMap.hpp"

class TileRenderer
{
public:
    TileRenderer();

    void render(sf::RenderTarget& target, Tile& tile, sf::Vector2f offset);

    void setAtlas(sf::Texture& atlas);

private:
    sf::Texture m_tileAtlas;
};

#endif // MSG_GAME_TILERENDERER_HPP

#ifndef MSG_GAME_TILEMAPRENDERER_HPP
#define MSG_GAME_TILEMAPRENDERER_HPP

#include "SFML/Graphics/RenderTexture.hpp"

#include "TileMap.hpp"

#include "TileRenderer.hpp"

class TileMapRenderer
{
public:
    TileMapRenderer();

    void render(sf::RenderTarget& target, TileMap& tileMap);

    void setTileAtlas(sf::Texture& texture);

private:
    TileRenderer m_tileRenderer;
    sf::RenderTexture m_texture;
};

#endif // MSG_GAME_TILEMAPRENDERER_HPP

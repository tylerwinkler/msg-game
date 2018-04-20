#ifndef MSG_GAME_CHUNKRENDERER_HPP
#define MSG_GAME_CHUNKRENDERER_HPP

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

#include "TileMap.hpp"

class ChunkRenderer
{
public:
    ChunkRenderer(int chunkWidth, int chunkHeight);

public:
    void render(sf::RenderTarget& target, const TileMap& tileMap, int chunkX, int chunkY);

    void update(const TileMap& tileMap, int chunkX, int chunkY);

private:
    sf::RenderTexture m_texture;
};

#endif // MSG_GAME_CHUNKRENDERER_HPP

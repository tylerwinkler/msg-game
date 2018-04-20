#include "ChunkRenderer.hpp"

ChunkRenderer::ChunkRenderer(int chunkWidth, int chunkHeight)
{
    m_texture.create(chunkWidth, chunkHeight);
}

void ChunkRenderer::render(sf::RenderTarget& target, const TileMap& tileMap, int chunkX, int chunkY)
{

}

void ChunkRenderer::update(const TileMap& tileMap, int chunkX, int chunkY)
{

}

#include "Tilemap/TileRenderer.hpp"

#include "SFML/Graphics/Sprite.hpp"

namespace
{
    const int AtlasResolution = 32;
}

TileRenderer::TileRenderer()
{
}

void TileRenderer::render(sf::RenderTarget& target, Tile& tile, sf::Vector2f offset)
{
    sf::Sprite sprite;
    sprite.setTexture(m_tileAtlas);

    sf::IntRect textureRect(AtlasResolution * tile.id, 0, AtlasResolution, AtlasResolution);

    sprite.setTextureRect(textureRect);

    sprite.setPosition(offset);

    target.draw(sprite);
}

void TileRenderer::setAtlas(sf::Texture& atlas)
{
    m_tileAtlas = std::move(atlas);
}

#include "Tilemap/TileMapRenderer.hpp"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"

#include "Tilemap/TileRenderer.hpp"

TileMapRenderer::TileMapRenderer()
{

}

void TileMapRenderer::render(sf::RenderTarget& target, TileMap& tileMap)
{
    sf::Vector2f offset;
    for (int i = 0; i < tileMap.getHeight(); ++i)
    {
        for (int j = 0; j < tileMap.getWidth(); ++j)
        {
            offset.x = j * 32;
            offset.y = i * 32;
            m_tileRenderer.render(target, tileMap.tileAt(j, i), offset);
        }
    }

//    for (int i = 1; i < tileMap.getHeight(); ++i)
//    {
//        sf::RectangleShape rect;
//        rect.setSize(sf::Vector2f(tileMap.getWidth() * 32, 1));
//        rect.setPosition(sf::Vector2f(0, 32 * i));
//        target.draw(rect);
//    }
//
//    for (int i = 1; i < tileMap.getWidth(); ++i)
//    {
//        sf::RectangleShape rect;
//        rect.setSize(sf::Vector2f(1, tileMap.getHeight() * 32));
//        rect.setPosition(sf::Vector2f(32 * i, 0));
//        target.draw(rect);
//    }
}

void TileMapRenderer::setTileAtlas(sf::Texture& atlas)
{
    m_tileRenderer.setAtlas(atlas);
}

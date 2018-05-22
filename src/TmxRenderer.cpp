#include "TmxRenderer.hpp"

#include "SFML/Graphics/Sprite.hpp"

#include "GameEngine.hpp"
#include "Global.hpp"
#include "TextureManager.hpp"

void TmxRenderer::render(sf::RenderTarget& target, TmxMap& map)
{
    sf::Texture& atlas = Global::game.getTextureManager().get("./assets/images/atlas.jpg");
    sf::Sprite sprite;
    sprite.setTexture(atlas);

    for (int i = 0; i < map.width; ++i)
    {
        for (int j = 0; j < map.height; ++j)
        {
            int tileId = map.tiles[j + map.width * i] - 1;

            sprite.setTextureRect(sf::IntRect(tileId * map.tileWidth, 0, map.tileWidth, map.tileHeight));

            sprite.setPosition(map.tileWidth * j, map.tileHeight * i);

            if (tileId != -1)
            target.draw(sprite);
        }
    }
}

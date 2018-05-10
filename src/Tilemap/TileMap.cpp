#include "Tilemap/TileMap.hpp"

TileMap::TileMap()
{
    for (int i = 0; i < getHeight(); ++i)
    {
        for (int j = 0; j < getWidth(); ++j)
        {
            m_tiles[j][i].id = Tile::WATER;
        }
    }
}

Tile& TileMap::raytrace(int x, int y)
{
    return m_tiles[x / (32)][y / (32)];
}

Tile& TileMap::tileAt(int x, int y)
{
    return m_tiles[x][y];
}

int TileMap::getWidth()
{
    return 64;
}

int TileMap::getHeight()
{
    return 64;
}

#ifndef MSG_GAME_TILEMAP_HPP
#define MSG_GAME_TILEMAP_HPP

#include <string>

struct Tile
{
    enum TileID
    {
        VOID,
        WATER,
        GRASS,
        WATER_GRATE,
        LAVA
    };

    int id;
};

class TileMap
{
public:
    TileMap();

public:
    bool loadFromFile(const std::string& filename);

    // raytrace will return the tile that contains the x, y coordinate
    Tile& raytrace(int x, int y);

    // Returns a reference to the tile located in the x, y position.
    Tile& tileAt(int x, int y);

    // Returns the number of tiles on the horizontal line
    int getWidth();

    // Returns the number of tiles on the vertical line
    int getHeight();

private:
    Tile m_tiles[64][64];
};

#endif // MSG_GAME_TILEMAP_HPP

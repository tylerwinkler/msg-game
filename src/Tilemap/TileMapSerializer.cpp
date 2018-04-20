#include "Tilemap/TileMapSerializer.hpp"

#include <fstream>
#include <sstream>

void TileMapSerializer::serialize(TileMap& map, const std::string& filename)
{
    std::ofstream file;
    file.open(filename);

    if (!file.good())
    {
        std::stringstream ss;
        ss << "Failed to open map file for writing: " << filename;

        throw std::runtime_error(ss.str());
    }

    std::stringstream ssOut;
    for (int i = 0; i < map.getHeight(); ++i)
    {
        for (int j = 0; j < map.getWidth(); ++j)
        {
            ssOut << map.tileAt(j, i).id << ' ';
        }
        ssOut << '\n';
    }

    file << ssOut.str();

    file.close();
}

TileMap TileMapSerializer::deserialize(std::string filename)
{
    TileMap output;

    std::ifstream file;
    file.open(filename);

    if (!file.good())
    {
        std::stringstream ss;
        ss << "Failed to open map file: " << filename;

        throw std::runtime_error(ss.str());
    }

    int x = 0;
    int y = 0;
    while (file.good())
    {
        std::string line;
        std::getline(file, line);

        std::stringstream ss(line);
        std::string tile = "";
        while (std::getline(ss, tile, ' '))
        {
            std::stringstream ss2(tile);
            int tileInt = Tile::WATER;
            ss2 >> tileInt;
            output.tileAt(x++, y).id = tileInt;
        }
        x = 0;
        ++y;
    }

    file.close();

    return output;
}

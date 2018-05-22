#ifndef MSG_GAME_TMXMAP_HPP
#define MSG_GAME_TMXMAP_HPP

#include <string>
#include <vector>

struct TmxMapEntity
{
    std::string type;
    int x;
    int y;

    std::vector<std::string> params;
}; // TmxMapEntity

struct TmxMap
{
    int width;
    int height;

    int tileWidth;
    int tileHeight;

    std::vector<int> tiles;

    std::vector<TmxMapEntity> objects;
}; // TmxMap

#endif // MSG_GAME_TMXMAP_HPP

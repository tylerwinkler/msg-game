#ifndef MSG_GAME_TILEMAPSERIALIZER_HPP
#define MSG_GAME_TILEMAPSERIALIZER_HPP

#include <string>

#include "TileMap.hpp"

// Serializer for the developmental tilemap and the "1.0" map
class TileMapSerializer
{
public:
    // This can be overridden to support new map versions
    virtual void serialize(TileMap& map, const std::string& filename);

    // This can be overridden to support new map versions
    virtual TileMap deserialize(std::string filename);
};
#endif // MSG_GAME_TILEMAPSERIALIZER_HPP

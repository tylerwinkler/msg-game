#ifndef MSG_GAME_TMXLOADER_HPP
#define MSG_GAME_TMXLOADER_HPP

#include <string>

#include "TmxMap.hpp"

class TmxLoader
{
public:
    static TmxMap loadFromFile(const std::string& filename);
}; // TmxLoader

#endif // MSG_GAME_TMXLOADER_HPP

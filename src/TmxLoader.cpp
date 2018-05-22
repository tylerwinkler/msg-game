#include "TmxLoader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace
{
    template <class T>
    T findValue(const std::string& searchValue, const std::string& str)
    {
        int foundPosition = -1;

        std::string searchVal = ' ' + searchValue;
        foundPosition = str.find(searchVal);

        if (foundPosition == std::string::npos)
        {
            std::stringstream errorStream;
            errorStream << "Failed to load map file. Tmx file format invalid.\n"
            << "Error on line: " << str << "\n";

            throw std::runtime_error(errorStream.str());
        }

        // Advance the position to be in the inside of the quotes for the value
        foundPosition += searchVal.length() + 2;

        std::string token = str.substr(foundPosition, str.find("\"", foundPosition) - foundPosition);

        std::cout << "Found " << searchVal << ". Value = " << token << "\n";

        std::stringstream ss(token);

        T output;

        ss >> output;

        return output;
    }

    void readFileHeader(TmxMap& map, std::ifstream& stream)
    {
        std::string lineBuffer;

        // Discard the first line - XML header
        std::getline(stream, lineBuffer);

        std::getline(stream, lineBuffer);

        map.width = findValue<int>("width", lineBuffer);
        map.height = findValue<int>("height", lineBuffer);

        map.tileWidth = findValue<int>("tilewidth", lineBuffer);
        map.tileHeight = findValue<int>("tileheight", lineBuffer);
    }

    void skipToTileData(std::ifstream& stream)
    {
        std::string lineBuffer = "";
        while (lineBuffer.find("data encoding") == std::string::npos)
        {
            std::getline(stream, lineBuffer);
        }
    }

    void readTileData(TmxMap& map, std::ifstream& stream)
    {
        std::string lineBuffer;
        for (int i = 0; i < map.height; ++i)
        {
            std::getline(stream, lineBuffer);
            std::stringstream ss(lineBuffer);
            for (int j = 0; j < map.width; ++j)
            {
                std::string tokenizedTile;
                std::getline(ss, tokenizedTile, ',');

                int tile = 0;
                std::stringstream ss1(tokenizedTile);

                ss1 >> tile;
                map.tiles.push_back(tile);

                std::cout << tile << ",";
            }
            std::cout << '\n';
        }
    }

    void skipToObjectData(std::ifstream& stream)
    {
        std::string lineBuffer = "";
        while (lineBuffer.find("objectgroup") == std::string::npos)
        {
            std::getline(stream, lineBuffer);
        }
    }

    void readObjectData(TmxMap& map, std::ifstream& stream)
    {
        std::string lineBuffer = "";
        while (lineBuffer.find("objectgroup") == std::string::npos)
        {
            std::getline(stream, lineBuffer);

            if (lineBuffer.find("objectgroup") != std::string::npos)
            {
                return;
            }

            TmxMapEntity e;
            e.type = findValue<std::string>("type", lineBuffer);
            e.x = findValue<int>("x", lineBuffer);
            e.y = findValue<int>("y", lineBuffer);

            map.objects.push_back(e);
        }
    }
}

TmxMap TmxLoader::loadFromFile(const std::string& filename)
{
    TmxMap map;

    std::ifstream file;

    file.open(filename);

    readFileHeader(map, file);

    skipToTileData(file);

    readTileData(map, file);

    skipToObjectData(file);

    readObjectData(map, file);

    file.close();

    return map;
}

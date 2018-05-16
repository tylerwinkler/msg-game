#ifndef MSG_GAME_FONTMANAGER_HPP
#define MSG_GAME_FONTMANAGER_HPP

#include <map>
#include <string>

#include "SFML/Graphics/Font.hpp"

class FontManager
{
public:
    sf::Font& get(const std::string& filename);

private:
    std::map<std::string, sf::Font> m_fonts;
}; // FontManager

#endif // MSG_GAME_FONTMANAGER_HPP

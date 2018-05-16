#include "FontManager.hpp"

sf::Font& FontManager::get(const std::string& filename)
{
    if (m_fonts.count(filename) != 0)
    {
        return m_fonts.at(filename);
    }

    sf::Font font;
    if (font.loadFromFile(filename))
    {
        m_fonts.insert(std::make_pair(filename, font));

        return m_fonts.at(filename);
    }

    throw std::runtime_error(filename + " could not be found.");
}


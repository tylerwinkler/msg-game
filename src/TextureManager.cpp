#include "TextureManager.hpp"

sf::Texture& TextureManager::get(const std::string& filename)
{
    if (m_textures.count(filename) != 0)
    {
        return m_textures.at(filename);
    }

    sf::Texture texture;
    if (texture.loadFromFile(filename))
    {
        m_textures.insert(std::make_pair(filename, texture));

        return m_textures.at(filename);
    }

    throw std::runtime_error(filename + " could not be found.");
}

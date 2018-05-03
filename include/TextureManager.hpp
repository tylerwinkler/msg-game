#ifndef MSG_GAME_TEXTUREMANAGER_HPP
#define MSG_GAME_TEXTUREMANAGER_HPP

#include <map>

#include "SFML/Graphics/Texture.hpp"

class TextureManager
{
public:
    sf::Texture& get(const std::string& filename);

private:
    std::map<std::string, sf::Texture> m_textures;
}; // TextureManager

#endif // MSG_GAME_TEXTUREMANAGER_HPP

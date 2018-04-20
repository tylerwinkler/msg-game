#ifndef MSG_GAME_CHARACTERRENDERER_HPP
#define MSG_GAME_CHARACTERRENDERER_HPP

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

#include "Character.hpp"

class CharacterRenderer
{
public:
    void setCircle(int radius, sf::Color color);

    void render(sf::RenderTarget& target, const Character& character);

private:
    sf::CircleShape m_circle;
};

#endif // MSG_GAME_CHARACTERRENDERER_HPP
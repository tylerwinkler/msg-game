#ifndef MSG_GAME_CHARACTERRENDERER_HPP
#define MSG_GAME_CHARACTERRENDERER_HPP

#include "SFML/Graphics/RenderTarget.hpp"

#include "Entities/Entity.hpp"

class CharacterRenderer
{
public:
    void render(sf::RenderTarget& target, Entity& character, float interpolation);

private:
};

#endif // MSG_GAME_CHARACTERRENDERER_HPP

#ifndef MSG_GAME_TMXRENDERER_HPP
#define MSG_GAME_TMXRENDERER_HPP

#include "SFML/Graphics/RenderTarget.hpp"

#include "TmxMap.hpp"

class TmxRenderer
{
public:
    void render(sf::RenderTarget& target, TmxMap& map);
};

#endif // MSG_GAME_TMXRENDERER_HPP

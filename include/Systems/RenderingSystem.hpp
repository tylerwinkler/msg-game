#ifndef MSG_GAME_SYSTEMS_RENDERINGSYSTEM_HPP

#include "Systems/System.hpp"

namespace RenderLayer
{
    Background,

}

class RenderingSystem : public System
{
public:
    void addSpriteComponent(SpriteComponent& component);

    void renderWorld();

    void renderMinimap();

private:
    std::multimap<int, SpriteComponent*> m_renderObjects;

    sf::View m_camera;
    sf::View m_minimapView;
}; // RenderingSystem

#endif // MSG_GAME_SYSTEMS_RENDERINGSYSTEM_HPP

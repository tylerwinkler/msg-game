#ifndef MSG_GAME_COMPONENTS_SPRITECOMPONENT_HPP
#define MSG_GAME_COMPONENTS_SPRITECOMPONENT_HPP

#include "SFML/Graphics/Sprite.hpp"

#include "Component.hpp"

class SpriteComponent : public Component
{
public:
    SpriteComponent();

public:
    bool init(Entity& owner);

    void update(Entity& owner);

private:
    sf::Sprite m_sprite;
};

#endif // MSG_GAME_COMPONENTS_SPRITECOMPONENT_HPP

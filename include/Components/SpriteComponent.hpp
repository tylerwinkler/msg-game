#ifndef MSG_GAME_COMPONENTS_SPRITECOMPONENT_HPP
#define MSG_GAME_COMPONENTS_SPRITECOMPONENT_HPP

#include <string>

#include "SFML/Graphics/Sprite.hpp"

#include "Component.hpp"

class SpriteComponent : public Component
{
public:
    SpriteComponent();

    SpriteComponent(const std::string& texture);

public:
    bool onInit(int ownerID) final override;

    void setPosition(sf::Vector2f position);

    void setRect(sf::IntRect rect);

    sf::Sprite& getSprite();

    void render(sf::RenderTarget& target);

    void receive(int x, int y) final override;

private:
    sf::Sprite m_sprite;
};

#endif // MSG_GAME_COMPONENTS_SPRITECOMPONENT_HPP

#include "Components/SpriteComponent.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

#include "Entities/Entity.hpp"

#include "Global.hpp"
#include "GameEngine.hpp"
#include "TextureManager.hpp"

SpriteComponent::SpriteComponent()
{
    type = ComponentType::SpriteComponent;
}

SpriteComponent::SpriteComponent(const std::string& texture) : SpriteComponent()
{
    m_sprite.setTexture(Global::game.getTextureManager().get(texture));
}

bool SpriteComponent::init(Entity& owner)
{
    return true;
}

void SpriteComponent::setPosition(sf::Vector2f position)
{
    m_sprite.setPosition(position);
}

void SpriteComponent::setRect(sf::IntRect rect)
{
    m_sprite.setTextureRect(rect);
}

sf::Sprite& SpriteComponent::getSprite()
{
    return m_sprite;
}

void SpriteComponent::render(sf::RenderTarget& target)
{
    target.draw(m_sprite);
}

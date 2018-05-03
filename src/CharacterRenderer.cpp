#include "CharacterRenderer.hpp"

void CharacterRenderer::setCircle(int radius, sf::Color color)
{
    m_circle.setRadius(radius);
    m_circle.setFillColor(color);

    m_circle.setOrigin(radius, radius);
}

void CharacterRenderer::render(sf::RenderTarget& target, const Entity& character)
{
    m_circle.setPosition(character.position);

    target.draw(m_circle);
}

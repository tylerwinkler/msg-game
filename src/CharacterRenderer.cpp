#include "CharacterRenderer.hpp"

#include "Components/SpriteComponent.hpp"

void CharacterRenderer::render(sf::RenderTarget& target, Entity& character, float interpolation)
{
    sf::Vector2f pos = character.oldPosition + (character.position - character.oldPosition) * interpolation;
    character.getComponent<SpriteComponent>().setPosition(pos);
    character.getComponent<SpriteComponent>().render(target);
}

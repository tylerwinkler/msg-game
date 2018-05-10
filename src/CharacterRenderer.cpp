#include "CharacterRenderer.hpp"

#include "Components/SpriteComponent.hpp"

void CharacterRenderer::render(sf::RenderTarget& target, Entity& character)
{
    character.getComponent<SpriteComponent>().setPosition(character.position);
    character.getComponent<SpriteComponent>().render(target);
}

#include "Entities/EntityFactory.hpp"

#include "Animation.hpp"

#include "Components/AnimationComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/ComponentFactory.hpp"
#include "Components/InteractionComponent.hpp"
#include "Components/LootComponent.hpp"

#include <iostream>

Entity EntityFactory::create(const std::string& entityType)
{
    const std::string& s = entityType;
    if (s == "torch")
    {
        return createTorch();
    }
    else if (s == "spawn")
    {
        // return createSpawn();
    }
    else if (s == "spawn")
    {
        // return createSpawn();
    }
    else if (s == "spawn")
    {
        // return createSpawn();
    }
    else if (s == "spawn")
    {
        // return createSpawn();
    }
    else if (s == "spawn")
    {
        // return createSpawn();
    }
    else if (s == "spawn")
    {
        // return createSpawn();
    }

    return std::move(createMapTransition(0));
    throw std::runtime_error("Entity not known to factory");
}

Entity EntityFactory::createMapTransition(int transitionId)
{
    Entity entity;

    entity.addComponent(ComponentFactory::createCollisionComponent(-24, -24, 48, 48));

    CollisionComponent& coll = entity.getComponent<CollisionComponent>();

    if (!entity.init())
    {
        throw std::logic_error("Failed to init Map Transition Entity");
    }

    return std::move(entity);
}

Entity EntityFactory::createCharacter(int characterId)
{
    Entity entity;

    entity.addComponent(ComponentFactory::createAnimationComponent());
    entity.addComponent(ComponentFactory::createCollisionComponent(0, 0, 32, 32));
    entity.addComponent(ComponentFactory::createHealthComponent());
    entity.addComponent(ComponentFactory::createSpriteComponent("./assets/images/character.png"));

    sf::Sprite& sprite = entity.getComponent<SpriteComponent>().getSprite();
    sprite.setOrigin(sprite.getLocalBounds().width / 2 / 3, sprite.getLocalBounds().height / 2 / 3);

    Animation walkLeft;
    walkLeft.loadFromFile("./assets/animations/characters/walkLeft.anim");
    entity.getComponent<AnimationComponent>().addAnimation("walkLeft", walkLeft);

    Animation walkRight;
    walkRight.loadFromFile("./assets/animations/characters/walkRight.anim");
    entity.getComponent<AnimationComponent>().addAnimation("walkRight", walkRight);

    Animation walkUp;
    walkUp.loadFromFile("./assets/animations/characters/walkUp.anim");
    entity.getComponent<AnimationComponent>().addAnimation("walkUp", walkUp);

    Animation walkDown;
    walkDown.loadFromFile("./assets/animations/characters/walkDown.anim");
    entity.getComponent<AnimationComponent>().addAnimation("walkDown", walkDown);

    if (!entity.init())
    {
        throw std::logic_error("Failed to init Character Entity");
    }

    return std::move(entity);
}

Entity EntityFactory::createTorch()
{
    Entity entity;

    entity.addComponent(ComponentFactory::createAnimationComponent());
    entity.addComponent(ComponentFactory::createSpriteComponent("./assets/images/torch.png"));

    Animation lightOn;
    lightOn.loadFromFile("./assets/animations/torch/on.anim");

    entity.getComponent<AnimationComponent>().addAnimation("lightOn", lightOn);

    Animation lightOff;
    lightOff.loadFromFile("./assets/animations/torch/off.anim");

    entity.getComponent<AnimationComponent>().addAnimation("lightOff", lightOff);

    if (!entity.init())
    {
        throw std::logic_error("Failed to init Torch Entity");
    }

    return std::move(entity);
}

Entity EntityFactory::createChest()
{
    Entity entity;

    entity.addComponent(ComponentFactory::createSpriteComponent("./assets/images/chest.png"));
    entity.addComponent(ComponentFactory::createLootComponent());
    entity.addComponent(ComponentFactory::createInteractionComponent());
    entity.addComponent(ComponentFactory::createCollisionComponent());

    entity.getComponent<LootComponent>().getItems().push_back(1);
    entity.getComponent<LootComponent>().getItems().push_back(1);

    if (!entity.init())
    {
        throw std::logic_error("Failed to init Chest Entity");
    }

    return std::move(entity);
}

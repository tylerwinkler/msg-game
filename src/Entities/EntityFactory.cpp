#include "Entities/EntityFactory.hpp"

#include "Animation.hpp"

#include "Components/AnimationComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/ComponentFactory.hpp"
#include "Components/InteractionComponent.hpp"
#include "Components/LootComponent.hpp"

#include "Systems/EntitySystem.hpp"

#include "GameEngine.hpp"
#include "Global.hpp"

int EntityFactory::create(const std::string& entityType)
{
    const std::string& s = entityType;
    if (s == "torch")
    {
        return createTorch();
    }
    else if (s == "tree")
    {
        return createTree();
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

    return createMapTransition(0);
    throw std::runtime_error("Entity not known to factory");
}

int EntityFactory::createMapTransition(int transitionId)
{
    int id = Global::game.getEntitySystem().getFreeEntity();
    Entity& entity = Global::game.getEntitySystem().getEntity(id);

    entity.addComponent(ComponentFactory::createCollisionComponent(-24, -24, 48, 48));

    entity.assignID(id);

    if (!entity.init())
    {
        throw std::logic_error("Failed to init Map Transition Entity");
    }

    return id;
}

int EntityFactory::createCharacter(int characterId)
{
    int id = Global::game.getEntitySystem().getFreeEntity();
    Entity& entity = Global::game.getEntitySystem().getEntity(id);

    entity.addComponent(ComponentFactory::createAnimationComponent());
    entity.addComponent(ComponentFactory::createCollisionComponent(0, 0, 32, 32));
    entity.addComponent(ComponentFactory::createHealthComponent());
    entity.addComponent(ComponentFactory::createSpriteComponent("./assets/images/character.png"));

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

    entity.assignID(id);

    if (!entity.init())
    {
        throw std::logic_error("Failed to init Character Entity");
    }

    return id;
}

int EntityFactory::createTorch()
{
    int id = Global::game.getEntitySystem().getFreeEntity();
    Entity& entity = Global::game.getEntitySystem().getEntity(id);

    entity.addComponent(ComponentFactory::createAnimationComponent());
    entity.addComponent(ComponentFactory::createSpriteComponent("./assets/images/torch.png"));
    entity.addComponent(ComponentFactory::createCollisionComponent(0, 0, 32, 32));

    CollisionComponent& coll = entity.getComponent<CollisionComponent>();
    coll.setCollisionFunc([&](CollisionComponent& other){
                            //if (entity.getComponent<LightComponent>().isActive())
                            {
                                entity.getComponent<AnimationComponent>().playAnimation("lightOff");
                            }
//                            else
//                            {
//                                entity.getComponent<AnimationComponent>().playAnimation("lightOn");
//                            }
                          });

    Animation lightOn;
    lightOn.loadFromFile("./assets/animations/torch/on.anim");

    Animation lightOff;
    lightOff.loadFromFile("./assets/animations/torch/off.anim");

    entity.getComponent<AnimationComponent>().addAnimation("lightOn", lightOn);
    entity.getComponent<AnimationComponent>().addAnimation("lightOff", lightOff);

    entity.assignID(id);

    if (!entity.init())
    {
        throw std::logic_error("Failed to init Torch Entity");
    }

    return id;
}

int EntityFactory::createChest()
{
    int id = Global::game.getEntitySystem().getFreeEntity();
    Entity& entity = Global::game.getEntitySystem().getEntity(id);

    entity.addComponent(ComponentFactory::createSpriteComponent("./assets/images/chest.png"));
    entity.addComponent(ComponentFactory::createLootComponent());
    entity.addComponent(ComponentFactory::createInteractionComponent());
    entity.addComponent(ComponentFactory::createCollisionComponent());

    entity.getComponent<LootComponent>().getItems().push_back(1);
    entity.getComponent<LootComponent>().getItems().push_back(1);

    entity.assignID(id);

    if (!entity.init())
    {
        throw std::logic_error("Failed to init Chest Entity");
    }

    return id;
}

int EntityFactory::createTree()
{
    int id = Global::game.getEntitySystem().getFreeEntity();
    Entity& entity = Global::game.getEntitySystem().getEntity(id);

    entity.addComponent(ComponentFactory::createSpriteComponent("./assets/images/tree.png"));
    entity.addComponent(ComponentFactory::createLootComponent());
    entity.addComponent(ComponentFactory::createInteractionComponent());
    entity.addComponent(ComponentFactory::createCollisionComponent(0, 16, 32, 32));

    entity.assignID(id);

    if (!entity.init())
    {
        throw std::logic_error("Failed to init Tree Entity");
    }

    return id;
}

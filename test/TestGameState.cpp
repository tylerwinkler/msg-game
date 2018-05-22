#include "TestGameState.hpp"

#include "SFML/Graphics/RenderWindow.hpp"

#include "Components/LootComponent.hpp"

#include "Systems/CollisionSystem.hpp"

#include "TmxRenderer.hpp"

#include <iostream>

#include "Systems/EntitySystem.hpp"

namespace {
    bool controls[] = {false, false, false, false};
    sf::Sprite spr;
    std::vector<Entity> ents;
    EntitySystem es;
}

void renderCollider(CollisionComponent& comp, sf::RenderTarget& target)
{
    sf::RectangleShape rect;
    rect.setPosition(comp.rect.left, comp.rect.top);
    rect.setSize(sf::Vector2f(comp.rect.width, comp.rect.height));
    rect.setFillColor(sf::Color(200, 150, 100, 150));
    rect.setOutlineThickness(-2.f);
    rect.setOutlineColor(sf::Color(200, 15, 100, 250));

    target.draw(rect);
}

bool TestGameState::init()
{
    map2 = TmxLoader::loadFromFile("./assets/maps/untitled.tmx");

    for (int i = 0; i < map2.objects.size(); ++i)
    {
        TmxMapEntity& ent = map2.objects[i];
        ents.push_back(EntityFactory::create(ent.type));
        ents.back().setPosition(ent.x, ent.y);
    }

    console.close();

    spr.setTexture(Global::game.getTextureManager().get("./assets/images/71b.png"));
    spr.setPosition(1600, 1400);

    map = serializer.deserialize("./assets/maps/edana.txt");

    player.getCharacter() = EntityFactory::createCharacter(0);
    player.getCharacter().position = sf::Vector2f(1500, 1500);

    mapRenderer.setTileAtlas(Global::game.getTextureManager().get("./assets/images/atlas.jpg"));

    camera.setCenter(player.getCharacter().position);
    camera.setSize(Global::game.getWindow().getView().getSize());

    trans = EntityFactory::createMapTransition(0);
    trans.setPosition(400, 400);

    std::function<void(Entity&)> cf = [](Entity& other){
                                                              other.setPosition(1500, 1500);
                          };
    trans.getComponent<CollisionComponent>().setCollisionFunc(cf);

    console.setFunction("exit", [&]{Global::game.quit();});
    console.setFunction("rosebud", [&]{player.getWallet().addGold(1000);});
    console.setFunction("respawn", [&]{player.getCharacter().getComponent<HealthComponent>().hp = 1.f; player.getCharacter().position = sf::Vector2f(150, 150);});
    console.setFunction("loadmap map", [&]{map = serializer.deserialize("./assets/maps/map.txt");});
    console.setFunction("loadmap edana", [&]{map = serializer.deserialize("./assets/maps/edana.txt");});


    mouseListeners.push_back(&editor);

    torch.setTexture(Global::game.getTextureManager().get("./assets/images/torch-unlit.png"));

    torch.setPosition(sf::Vector2f(300, 300));

    light.setTexture(Global::game.getTextureManager().get("./assets/images/torch-light.png"));
    light.setPosition(sf::Vector2f(300, 300));
    light.setOrigin(256 - torch.getOrigin().x, 256 - torch.getOrigin().y);
    light.setColor(sf::Color(200, 150, 100));

    lightmap.create(map.getWidth() * 64, map.getHeight() * 64);

    blackbox.setSize(sf::Vector2f(map.getWidth() * 64, map.getHeight() * 64));
    blackbox.setFillColor(sf::Color(100, 100, 100));

    buffer.loadFromFile("./assets/sound/waterfall_.ogg");

    sound.setBuffer(buffer);

    sound.setPosition(300.f, 0.f, 300.f);
    sound.setVolume(0.3f);
    sound.setLoop(true);
    sound.play();

    torch2 = EntityFactory::createTorch();
    torch2.position = sf::Vector2f(500, 500);
    torch2.getComponent<AnimationComponent>().playAnimation("lightOn");

    player.getCharacter().getComponent<AnimationComponent>().playAnimation("walkDown");

    Global::game.getAnimationSystem().addComponent(&torch2.getComponent<AnimationComponent>());
    Global::game.getAnimationSystem().addComponent(&player.getCharacter().getComponent<AnimationComponent>());

    Global::game.getWindow().setKeyRepeatEnabled(false);

    character = EntityFactory::createCharacter(0);
    character.position = sf::Vector2f(600, 600);
    character.getComponent<AnimationComponent>().playAnimation("walkDown");
    Global::game.getAnimationSystem().addComponent(&character.getComponent<AnimationComponent>());

    Global::game.getCollisionSystem().addComponent(&player.getCharacter().getComponent<CollisionComponent>());
    Global::game.getCollisionSystem().addComponent(&trans.getComponent<CollisionComponent>());

    for (int i = 0; i < ents.size(); ++i)
    {
        //ents[i].getComponent<AnimationComponent>().playAnimation("lightOn");
    }

    chest = EntityFactory::createChest();
    chest.position = sf::Vector2f(40, 200);
    chest.getComponent<SpriteComponent>().getSprite().setPosition(sf::Vector2f(40, 200));

    m_interact = false;
    m_sprint = false;

    trans.getComponent<CollisionComponent>().getOwner().setPosition(600, 200);

    return true;
}

void TestGameState::onResize(int width, int height)
{
    camera.setSize(width, height);
}

void TestGameState::onMouseButton(int x, int y, int button, bool pressed)
{
    if (pressed)
    {
        if (ImGui::IsAnyItemHovered() || ImGui::IsAnyItemActive())
        {
            return;
        }
    }
//                selectedTile = &map.raytrace(
//                                             window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), camera).x,
//                                              window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), camera).y);
    for (auto listener : mouseListeners)
    {
        listener->onMouseButton(x, y, sf::Mouse::Button(button), pressed);
    }
}

void TestGameState::onMouseWheelMoved(float delta)
{
    if (delta > 0)
    {
        camera.zoom(0.9f);
    }
    else
    {
        camera.zoom(1.1f);
    }
}

void TestGameState::onKey(int keyCode, bool control, bool alt, bool shift, bool system, bool pressed)
{
    if (pressed)
    {
        if (console.isOpen())
        {
            if (keyCode == sf::Keyboard::Tilde)
            {
                console.toggle();
            }
        }
    }

    m_sprint = shift;
    switch (keyCode)
    {
    case sf::Keyboard::W:
        controls[UP] = pressed;
        break;
    case sf::Keyboard::S:
        controls[DOWN] = pressed;
        break;
    case sf::Keyboard::A:
        controls[LEFT] = pressed;
        break;
    case sf::Keyboard::D:
        controls[RIGHT] = pressed;
        break;
    case sf::Keyboard::E:
        m_interact = pressed;
        break;
    case sf::Keyboard::G:
        {
    //                        Entity swap = player.getCharacter();
    //                        player.getCharacter() = character;
    //                        character = swap;
        }
        break;
    case sf::Keyboard::T:
        if (pressed)
        {
            if (torchLit)
            {
                torch2.getComponent<AnimationComponent>().playAnimation("lightOff");
            }
            else
            {
                torch2.getComponent<AnimationComponent>().playAnimation("lightOn");
            }
            torchLit = !torchLit;
        }
        break;
    case sf::Keyboard::Tilde:
        if (pressed)
        {
            console.toggle();
        }
        break;
    case sf::Keyboard::F1:
        if (pressed)
        {
            lightControl = !lightControl;
        }
        break;
    default:
        break;
    }
}

void TestGameState::update()
{
    Global::game.getAnimationSystem().update(deltaClock.restart().asSeconds());

    sf::Vector2f velocity(0, 0);
    player.getCharacter().getComponent<AnimationComponent>().pauseAnimation();
    if (controls[UP])
    {
        velocity.y -= action == "Swimming" ? 10 : action == "Burning" ? 2 : 15;
        player.getCharacter().getComponent<AnimationComponent>().playAnimation("walkUp");
    }
    if (controls[DOWN])
    {
        velocity.y += action == "Swimming" ? 10 : action == "Burning" ? 2 : 15;
        player.getCharacter().getComponent<AnimationComponent>().playAnimation("walkDown");
    }
    if (controls[LEFT])
    {
        velocity.x -= action == "Swimming" ? 10 : action == "Burning" ? 2 : 15;
        player.getCharacter().getComponent<AnimationComponent>().playAnimation("walkLeft");
    }
    if (controls[RIGHT])
    {
        velocity.x += action == "Swimming" ? 10 : action == "Burning" ? 2 : 15;
        player.getCharacter().getComponent<AnimationComponent>().playAnimation("walkRight");
    }

    if (velocity.x != 0 && velocity.y != 0)
    {
        static float hypotenuse = std::sqrt(2) / 2;
        velocity.x = hypotenuse * velocity.x;
        velocity.y = hypotenuse * velocity.y;
    }//

    if (m_sprint)
    {
        velocity.x *= 1.5;
        velocity.y *= 1.5;
    }

    sf::Vector2f destination = player.getCharacter().position + velocity;

    int id = map.raytrace(destination.x, destination.y).id;

    switch (id)
    {
    case Tile::WATER:
        if (CanSwim)
        {
            action = "Swimming";
        }
        else
        {
            //velocity = sf::Vector2f(0, 0);
        }
        break;
    case Tile::LAVA:
        action = "Burning";
        player.getCharacter().getComponent<HealthComponent>().hp -= 0.01f;
        break;
    default:
        action = "Walking";
        break;
    }

    if (player.getCharacter().getComponent<HealthComponent>().hp > 0.0)
    {
        sf::Vector2f finalDestination = player.getCharacter().position;
        finalDestination += velocity;

        player.getCharacter().setPosition(finalDestination.x, finalDestination.y);
    }

    if (velocity == sf::Vector2f(0, 0))
    {
        action = "Idle";
    }

    if (m_interact)
    {
        sf::FloatRect interact;
        interact.width = 16;
        interact.height = 16;
        interact.left = player.getCharacter().position.x - 24;
        interact.top = player.getCharacter().position.y;

        if (interact.intersects(chest.getComponent<SpriteComponent>().getSprite().getGlobalBounds()))
        {
            lootWin.open(chest.getComponent<LootComponent>());
//            if (!chest.getComponent<LootComponent>().getItems().empty())
//            {
//                chest.getComponent<LootComponent>().getItems().pop_back();
//                player.getInventory().addItem("Dagger from chest");
//            }
        }
    }

    m_interact = false;

    sf::Listener::setPosition(player.getCharacter().position.x, 0, player.getCharacter().position.y);

    camera.setCenter(player.getCharacter().position);

    Global::game.getCollisionSystem().update();

    if (torch.getGlobalBounds().contains(player.getCharacter().position))
    {
        if (torchClock.getElapsedTime().asSeconds() >= seconds + 3)
        {
            if (!torchLit)
            {
                torch.setTexture(Global::game.getTextureManager().get("./assets/images/torch-lit.png"));
            }
            else
            {
                torch.setTexture(Global::game.getTextureManager().get("./assets/images/torch-unlit.png"));
            }
            torchLit = !torchLit;
            seconds = torchClock.getElapsedTime().asSeconds();
        }

    }
}

void TestGameState::render()
{
    sf::RenderWindow& window = Global::game.getWindow();
    window.setView(camera);

    //mapRenderer.render(window, map);
    TmxRenderer renderer;
    renderer.render(window, map2);

    window.draw(spr);

    characterRenderer.render(window, player.getCharacter());
    characterRenderer.render(window, character);

    renderCollider(trans.getComponent<CollisionComponent>(), window);
    renderCollider(player.getCharacter().getComponent<CollisionComponent>(), window);

    window.draw(torch);

    torch2.getComponent<SpriteComponent>().render(window);
    chest.getComponent<SpriteComponent>().render(window);

    lightmap.clear();
    lightmap.draw(blackbox);
    if (torchLit)
    {
        if (lightControl)
        {
            light.setPosition(player.getCharacter().position);
            lightmap.draw(light);
        }
        else
        lightmap.draw(light, sf::BlendAdd);
    }
    lightmap.display();
    lightmapSprite.setTexture(lightmap.getTexture());

    window.draw(lightmapSprite, sf::BlendMultiply);

    for (int i = 0; i < ents.size(); ++i)
    {
        if (ents[i].hasComponent(SpriteComponent()))
        window.draw(ents[i].getComponent<SpriteComponent>().getSprite());
    }

    window.setView(window.getDefaultView());
    lootWin.render(window);
}

void TestGameState::cleanup()
{

}


void TestGameState::imguiUpdate()
{
    ImGui::Begin("Frame Time");
    std::stringstream ss2;
    float time = frameTime.restart().asSeconds();
    ss2 << "FrameTime: " << time;
    ss2 << "\nFPS: " << 1.0f / time;
    ss2 << "\nTotal Runtime: " << torchClock.getElapsedTime().asSeconds();
    ImGui::Text(ss2.str().c_str());
    ImGui::End();

    // Player stats
    ImGui::Begin("");
    ImGui::Text(std::string("Status: " + action).c_str());
    if (player.getCharacter().getComponent<HealthComponent>().hp > 0.0)
    {
        const int maxhealth = 150;
        float hp = player.getCharacter().getComponent<HealthComponent>().hp * maxhealth;
        std::stringstream ss;
        ss << hp << "/" << maxhealth;
        ImGui::Text(ss.str().c_str());
    }
    else
    {
        ImGui::Text("You are dead");
    }
    std::stringstream ss;
    ss << player.getWallet().getGold();
    ImGui::Text(std::string("Gold: " + ss.str()).c_str());
    ImGui::End();

    ImGui::Begin("Shop");
    if (ImGui::Button("Buy Dagger: 500g"))
    {
        if (player.getWallet().hasGold(500))
        {
            player.getWallet().removeGold(500);
            player.getInventory().addItem("Dagger from shop");
        }
    }
    ImGui::End();

    ImGui::Begin("Inventory");
    for (int i = 0; i < player.getInventory().getSize(); ++i)
    {
        ImGui::Text(player.getInventory().getItemInSlot(i).c_str());
    }
    ImGui::End();

    ImGui::Begin("Tilemap Editor!");
    if (ImGui::Button("Set to Grass"))
    {
        if (selectedTile)
        {
            selectedTile->id = Tile::GRASS;
        }
    }
    if (ImGui::Button("Set to Water"))
    {
        if (selectedTile)
        {
            selectedTile->id = Tile::WATER;
        }
    }
    if (ImGui::Button("Set to Water_Grate"))
    {
        if (selectedTile)
        {
            selectedTile->id = Tile::WATER_GRATE;
        }
    }
    if (ImGui::Button("Save to file"))
    {
        serializer.serialize(map, "./assets/maps/edana.txt");
    }
    if (ImGui::Button("Reload"))
    {
        map = serializer.deserialize("./assets/maps/edana.txt");
    }
    ImGui::End();

    if (console.isOpen())
    {
        console.draw();
    }
}

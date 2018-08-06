#include "TestGameState.hpp"

#include <iostream>
#include <fstream>

#include "SFML/Graphics/RenderWindow.hpp"

#include "Components/BankComponent.hpp"
#include "Components/ComponentFactory.hpp"
#include "Components/DialogComponent.hpp"
#include "Components/LootComponent.hpp"

#include "Systems/CollisionSystem.hpp"
#include "Systems/EntitySystem.hpp"

#include "ItemList.hpp"
#include "TmxRenderer.hpp"

namespace {
    bool controls[] = {false, false, false, false};
    sf::Sprite spr;
    std::vector<int> ents;
    bool lerp = true;

    sf::Vector2f mouseDestination;
    bool mouseMove = false;

    sf::Sprite flagSpr;
    sf::Texture flagTex;

    int dialogCharacter;
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

    if (!flagTex.loadFromFile("./assets/images/flag.png"))
    {
        return false;
    }
    flagSpr.setTexture(flagTex);

    for (size_t i = 0; i < map2.objects.size(); ++i)
    {
        TmxMapEntity& ent = map2.objects[i];

        int eid = EntityFactory::create(ent.type);

        Global::game.getEntitySystem().getEntity(eid).setPosition(ent.x, ent.y);

        ents.push_back(eid);
    }

    for (size_t i = 0; i < 100; ++i)
    {
        trees[i] = EntityFactory::createTree();

        Entity& e = Global::game.getEntitySystem().getEntity(trees[i]);

        e.setPosition(31 * i, 0);

        Global::game.getCollisionSystem().addComponent(&e.getComponent<CollisionComponent>());
    }
    for (size_t i = 1; i < 100; ++i)
    {
        trees[i + 100] = EntityFactory::createTree();

        Entity& e = Global::game.getEntitySystem().getEntity(trees[i + 100]);

        e.setPosition(0, 31 * i);

        Global::game.getCollisionSystem().addComponent(&e.getComponent<CollisionComponent>());
    }
    {
        trees[100] = EntityFactory::createTree();

        Entity& e = Global::game.getEntitySystem().getEntity(trees[100]);

        e.setPosition(500, 500);

        Global::game.getCollisionSystem().addComponent(&e.getComponent<CollisionComponent>());
    }

    console.close();

    spr.setTexture(Global::game.getTextureManager().get("./assets/images/71b.png"));
    spr.setPosition(1600, 1400);

    map = serializer.deserialize("./assets/maps/edana.txt");

    player.setCharacterID(EntityFactory::createCharacter(0));

    std::ifstream in;
    in.open("./saves/save.sav");

    int gold = 0;
    in >> gold;
    in.close();

    player.getWallet().setGold(gold);

    Global::game.getEntitySystem().getEntity(player.getCharacterID()).setPosition(1500, 1500);

    mapRenderer.setTileAtlas(Global::game.getTextureManager().get("./assets/images/atlas.jpg"));

    camera.setCenter(Global::game.getEntitySystem().getEntity(player.getCharacterID()).position);
    camera.setSize(Global::game.getWindow().getView().getSize());

    transID = EntityFactory::createMapTransition(0);
    Entity& trans = Global::game.getEntitySystem().getEntity(transID);
    trans.setPosition(400, 400);

    std::function<void(CollisionComponent&)> cf = [](CollisionComponent& other){
                                                              Global::game.getEntitySystem().getEntity(other.getOwnerID()).setPosition(1500, 1500);
                          };
    trans.getComponent<CollisionComponent>().setCollisionFunc(cf);

    Entity& playerCharacter = Global::game.getEntitySystem().getEntity(player.getCharacterID());

    console.setFunction("exit", [&]{Global::game.quit();});
    console.setFunction("rosebud", [&]{player.getWallet().addGold(1000);});
    console.setFunction("respawn", [&]{playerCharacter.getComponent<HealthComponent>().hp = 1.f; playerCharacter.position = sf::Vector2f(150, 150);});
    console.setFunction("loadmap map", [&]{map = serializer.deserialize("./assets/maps/map.txt");});
    console.setFunction("loadmap edana", [&]{map = serializer.deserialize("./assets/maps/edana.txt");});
    console.setFunction("ghost", [&]{playerCharacter.getComponent<CollisionComponent>().trigger = true;});

    console.setFunction("printitems", [&]
                        {
                            for (auto& item : ItemList::getItems())
                            {
                                std::cout << item.m_id << " : " << item.m_name << "\n";
                            }
                        });

    mouseListeners.push_back(&editor);

    torch.setTexture(Global::game.getTextureManager().get("./assets/images/torch-unlit.png"));

    torch.setPosition(sf::Vector2f(300, 300));

    light.setTexture(Global::game.getTextureManager().get("./assets/images/torch-light.png"));
    light.setPosition(sf::Vector2f(300, 300));
    light.setOrigin(256 - torch.getOrigin().x, 256 - torch.getOrigin().y);
    light.setColor(sf::Color(200, 150, 100));

    lightmap.create(map2.width * map2.tileWidth, map2.height * map2.tileHeight);

    blackbox.setSize(sf::Vector2f(map2.width * map2.tileWidth, map2.height * map2.tileHeight));
    blackbox.setFillColor(sf::Color(100, 100, 100));

    buffer.loadFromFile("./assets/sound/waterfall_.ogg");

    sound.setBuffer(buffer);

    sound.setPosition(300.f, 0.f, 300.f);
    sound.setVolume(0.3f);
    sound.setLoop(true);
    //sound.play();

    torch2ID = EntityFactory::createTorch();
    Entity& torch2 = Global::game.getEntitySystem().getEntity(torch2ID);
    torch2.position = sf::Vector2f(500, 500);
    torch2.getComponent<AnimationComponent>().playAnimation("lightOn");

    playerCharacter.getComponent<AnimationComponent>().playAnimation("walkDown");

    Global::game.getAnimationSystem().addComponent(&torch2.getComponent<AnimationComponent>());
    Global::game.getAnimationSystem().addComponent(&playerCharacter.getComponent<AnimationComponent>());

    Global::game.getWindow().setKeyRepeatEnabled(false);

    Global::game.getCollisionSystem().addComponent(&playerCharacter.getComponent<CollisionComponent>());
    Global::game.getCollisionSystem().addComponent(&trans.getComponent<CollisionComponent>());

    for (size_t i = 0; i < ents.size(); ++i)
    {
        //ents[i].getComponent<AnimationComponent>().playAnimation("lightOn");
    }

    chestID = EntityFactory::createChest();
    Entity& chest = Global::game.getEntitySystem().getEntity(chestID);
    chest.setPosition(40, 200);

    m_interact = false;
    m_sprint = false;

    dialogCharacter = EntityFactory::createCharacter(0);
    //dialogCharacter.onClick = EntityFunctions::Dialog;

    incrementer = 0;

    return true;
}

void TestGameState::onResize(int width, int height)
{
    camera.setSize(width, height);
    ui.setSize(width, height);
}

void TestGameState::onMouseButton(int x, int y, int button, bool pressed)
{
    if (pressed)
    {
        if (ImGui::IsAnyItemHovered() || ImGui::IsAnyItemActive())
        {
            return;
        }
        mouseDestination = Global::game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(Global::game.getWindow()), camera);
        mouseMove = true;
    }
    else
    {
        //mouseMove = false;
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

        if (keyCode == sf::Keyboard::Escape)
        {
            lootWin.close();
            diagWin.close();
            bankWin.close();
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
    case sf::Keyboard::H:
        lerp = pressed;
        break;
    case sf::Keyboard::G:
        {
            auto c = ComponentFactory::createDialogComponent();
            diagWin.open((DialogComponent&)*c.get());
        }
        break;
    case sf::Keyboard::B:
        {
            BankComponent bank;
            bank.items.push_back("Sword");
            bank.items.push_back("Shield");
            bank.items.push_back("Bow");
            bank.items.push_back("12 Arrows");
            bank.items.push_back("Saradomin Godsword");

            bankWin.open(bank);
        }
        break;
    case sf::Keyboard::T:
        if (pressed)
        {
            if (torchLit)
            {
                Global::game.getEntitySystem().getEntity(torch2ID).getComponent<AnimationComponent>().playAnimation("lightOff");
            }
            else
            {
                Global::game.getEntitySystem().getEntity(torch2ID).getComponent<AnimationComponent>().playAnimation("lightOn");
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
    Global::game.getCollisionSystem().prepare();

    Entity& playerCharacter = Global::game.getEntitySystem().getEntity(player.getCharacterID());

    sf::Vector2f velocity(0, 0);
    if (controls[UP])
    {
        velocity.y -= action == "Swimming" ? 10 : action == "Burning" ? 2 : 5;
        playerCharacter.getComponent<AnimationComponent>().playAnimation("walkUp");
    }
    if (controls[DOWN])
    {
        velocity.y += action == "Swimming" ? 10 : action == "Burning" ? 2 : 5;
        playerCharacter.getComponent<AnimationComponent>().playAnimation("walkDown");
    }
    if (controls[LEFT])
    {
        velocity.x -= action == "Swimming" ? 10 : action == "Burning" ? 2 : 5;
        playerCharacter.getComponent<AnimationComponent>().playAnimation("walkLeft");
    }
    if (controls[RIGHT])
    {
        velocity.x += action == "Swimming" ? 10 : action == "Burning" ? 2 : 5;
        playerCharacter.getComponent<AnimationComponent>().playAnimation("walkRight");
    }

    if (velocity.x != 0 && velocity.y != 0)
    {
        static float hypotenuse = std::sqrt(2) / 2;
        velocity.x = hypotenuse * velocity.x;
        velocity.y = hypotenuse * velocity.y;
    }

    if (m_sprint)
    {
        velocity.x *= 15;
        velocity.y *= 15;
    }

    sf::Vector2f destination = playerCharacter.position + velocity;

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
        playerCharacter.getComponent<HealthComponent>().hp -= 0.01f;
        break;
    default:
        action = "Walking";
        break;
    }

    if (playerCharacter.getComponent<HealthComponent>().hp > 0.0)
    {
        sf::Vector2f finalDestination = playerCharacter.position;
        finalDestination += velocity;

        playerCharacter.setPosition(finalDestination.x, finalDestination.y); // WASD movement
    }

    if (mouseMove)
    {
        //mouseDestination = Global::game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(Global::game.getWindow()), camera);

        float distanceSquared = (mouseDestination.x - playerCharacter.position.x) * (mouseDestination.x - playerCharacter.position.x) +
        (mouseDestination.y - playerCharacter.position.y) * (mouseDestination.y - playerCharacter.position.y);

        flagSpr.setPosition(mouseDestination);

        float x = mouseDestination.x - playerCharacter.position.x;
        float y = mouseDestination.y - playerCharacter.position.y;

        float total = std::abs(x) + std::abs(y);

        x /= total;
        y /= total;

        x *= 5;
        y *= 5;

        if (distanceSquared < 24 * 24)
        {
            mouseMove = false;
        }
        else
        {
            playerCharacter.setPosition(playerCharacter.position.x + x, playerCharacter.position.y + y);
        }
    }

    if (velocity == sf::Vector2f(0, 0))
    {
        action = "Idle";
        playerCharacter.getComponent<AnimationComponent>().pauseAnimation();
    }

    if (m_interact)
    {
        sf::FloatRect interact;
        interact.width = 16;
        interact.height = 16;
        interact.left = playerCharacter.position.x - 24;
        interact.top = playerCharacter.position.y;

        if (interact.intersects(Global::game.getEntitySystem().getEntity(chestID).getComponent<SpriteComponent>().getSprite().getGlobalBounds()))
        {
            lootWin.open(Global::game.getEntitySystem().getEntity(chestID).getComponent<LootComponent>());
        }
    }

    m_interact = false;

    sf::Listener::setPosition(playerCharacter.position.x, 0, playerCharacter.position.y);

    Global::game.getCollisionSystem().update();

    camera.setCenter(playerCharacter.position);

    ++incrementer;
    if (incrementer >= Global::game.getUPS() * 5)
    {
        incrementer = 0;
        player.getWallet().addGold(1);
    }

//    if (torch.getGlobalBounds().contains(player.getCharacter().position))
//    {
//        if (torchClock.getElapsedTime().asSeconds() >= seconds + 3)
//        {
//            if (!torchLit)
//            {
//                torch.setTexture(Global::game.getTextureManager().get("./assets/images/torch-lit.png"));
//            }
//            else
//            {
//                torch.setTexture(Global::game.getTextureManager().get("./assets/images/torch-unlit.png"));
//            }
//            torchLit = !torchLit;
//            seconds = torchClock.getElapsedTime().asSeconds();
//        }
//
//    }
}

void TestGameState::render(float interpolation)
{
    sf::RenderWindow& window = Global::game.getWindow();
    window.setView(camera);

    //mapRenderer.render(window, map);
    TmxRenderer renderer;
    renderer.render(window, map2);

    window.draw(spr);

    if (lerp)
    {
        characterRenderer.render(window, Global::game.getEntitySystem().getEntity(player.getCharacterID()), interpolation);
    }
    else
    {
        characterRenderer.render(window, Global::game.getEntitySystem().getEntity(player.getCharacterID()), 1.f);
    }

    renderCollider(Global::game.getEntitySystem().getEntity(transID).getComponent<CollisionComponent>(), window);
    renderCollider(Global::game.getEntitySystem().getEntity(player.getCharacterID()).getComponent<CollisionComponent>(), window);

    for (int i = 0; i < 200; ++i)
    {
        Entity& e = Global::game.getEntitySystem().getEntity(trees[i]);
        window.draw(e.getComponent<SpriteComponent>().getSprite());
        renderCollider(e.getComponent<CollisionComponent>(), window);
    }

//    window.draw(torch);

    Global::game.getEntitySystem().getEntity(torch2ID).getComponent<SpriteComponent>().render(window);
    Global::game.getEntitySystem().getEntity(chestID).getComponent<SpriteComponent>().render(window);

    lightmap.clear();
    lightmap.draw(blackbox);
    if (torchLit)
    {
        if (lightControl)
        {
            light.setPosition(Global::game.getEntitySystem().getEntity(player.getCharacterID()).position);
            lightmap.draw(light);
        }
        else
        lightmap.draw(light, sf::BlendAdd);
    }
    lightmap.display();
    lightmapSprite.setTexture(lightmap.getTexture());

    if (mouseMove)
    window.draw(flagSpr);

    window.draw(lightmapSprite, sf::BlendMultiply);

    for (size_t i = 0; i < ents.size(); ++i)
    {
        if (Global::game.getEntitySystem().getEntity(ents[i]).hasComponent(SpriteComponent()))
        window.draw(Global::game.getEntitySystem().getEntity(ents[i]).getComponent<SpriteComponent>().getSprite());
    }

    window.setView(ui);
    lootWin.render(window);
    diagWin.render(window);
    bankWin.render(window);
}

void TestGameState::cleanup()
{
    std::cout << "TestGameState::cleanup()\n";

    std::ofstream out;
    out.open("./saves/save.sav");

    out << player.getWallet().getGold() << "\n";

    out.close();
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
    if (Global::game.getEntitySystem().getEntity(player.getCharacterID()).getComponent<HealthComponent>().hp > 0.0)
    {
        const int maxhealth = 150;
        float hp = Global::game.getEntitySystem().getEntity(player.getCharacterID()).getComponent<HealthComponent>().hp * maxhealth;
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

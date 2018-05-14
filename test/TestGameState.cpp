#include "TestGameState.hpp"

namespace {bool controls[] = {false, false, false, false};}

bool TestGameState::init()
{
    console.close();

    map = serializer.deserialize("./assets/maps/edana.txt");

    player.getCharacter() = EntityFactory::createCharacter(0);
    player.getCharacter().position = sf::Vector2f(150, 150);

    mapRenderer.setTileAtlas(Global::game.getTextureManager().get("./assets/images/atlas.jpg"));

    camera.setCenter(player.getCharacter().position);
    camera.setSize(Global::game.getWindow().getView().getSize());

    trans = EntityFactory::createMapTransition(0);
    trans.position = sf::Vector2f(400, 400);

    rect.setPosition(trans.position.x + trans.getComponent<CollisionComponent>().x, trans.position.y + trans.getComponent<CollisionComponent>().y);
    rect.setSize(sf::Vector2f(trans.getComponent<CollisionComponent>().width, trans.getComponent<CollisionComponent>().height));
    rect.setFillColor(sf::Color(200, 0, 0, 150));
    rect.setOutlineColor(sf::Color(200, 0, 0, 250));
    rect.setOutlineThickness(5.f);

    trans.getComponent<CollisionComponent>().setCollisionFunc([&]{
                            map = serializer.deserialize("./assets/maps/map.txt");
                            trans.position = sf::Vector2f(0, 0);
                            rect.setPosition(trans.position.x + trans.getComponent<CollisionComponent>().x, trans.position.y + trans.getComponent<CollisionComponent>().y);
                          });

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

    animationSystem.addComponent(&torch2.getComponent<AnimationComponent>());
    animationSystem.addComponent(&player.getCharacter().getComponent<AnimationComponent>());

    Global::game.getWindow().setKeyRepeatEnabled(false);

    character = EntityFactory::createCharacter(0);
    character.position = sf::Vector2f(600, 600);
    character.getComponent<AnimationComponent>().playAnimation("walkDown");
    animationSystem.addComponent(&character.getComponent<AnimationComponent>());

    return true;
}

void TestGameState::handleEvent(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        Global::game.quit();
        break;
    case sf::Event::Resized:
        camera.setSize(event.size.width, event.size.height);
        break;
    case sf::Event::MouseButtonPressed:
        if (ImGui::IsAnyItemHovered() || ImGui::IsAnyItemActive())
        {
            break;
        }
//                selectedTile = &map.raytrace(
//                                             window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), camera).x,
//                                              window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), camera).y);
        for (auto listener : mouseListeners)
        {
            listener->onMouseButton(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button, true);
        }
        break;
    case sf::Event::KeyPressed:
        if (console.isOpen())
        {
            if (event.key.code == sf::Keyboard::Tilde)
            {
                console.toggle();
            }
        }
        switch (event.key.code)
        {
        case sf::Keyboard::W:
            controls[UP] = true;
            player.getCharacter().getComponent<AnimationComponent>().playAnimation("walkUp");
            break;
        case sf::Keyboard::S:
            controls[DOWN] = true;
            player.getCharacter().getComponent<AnimationComponent>().playAnimation("walkDown");
            break;
        case sf::Keyboard::A:
            controls[LEFT] = true;
            player.getCharacter().getComponent<AnimationComponent>().playAnimation("walkLeft");
            break;
        case sf::Keyboard::D:
            controls[RIGHT] = true;
            player.getCharacter().getComponent<AnimationComponent>().playAnimation("walkRight");
            break;
        case sf::Keyboard::G:
            {
//                        Entity swap = player.getCharacter();
//                        player.getCharacter() = character;
//                        character = swap;
            }
            break;
        case sf::Keyboard::T:
            if (torchLit)
            {
                torch2.getComponent<AnimationComponent>().playAnimation("lightOff");
            }
            else
            {
                torch2.getComponent<AnimationComponent>().playAnimation("lightOn");
            }
            torchLit = !torchLit;
            break;
        case sf::Keyboard::Tilde:
            console.toggle();
            break;
        case sf::Keyboard::F1:
            lightControl = !lightControl;
            break;
        default:
            break;
        }
        break;
    case sf::Event::KeyReleased:
        switch (event.key.code)
        {
        case sf::Keyboard::W:
            controls[UP] = false;
            break;
        case sf::Keyboard::S:
            controls[DOWN] = false;
            break;
        case sf::Keyboard::A:
            controls[LEFT] = false;
            break;
        case sf::Keyboard::D:
            controls[RIGHT] = false;
            break;
        default:
            break;
        }
        break;
    case sf::Event::MouseWheelMoved:
        if (event.mouseWheel.delta > 0)
        {
            camera.zoom(0.9f);
        }
        else
        {
            camera.zoom(1.1f);
        }
        break;
    default:
        break;
    }
}

void TestGameState::update()
{
    animationSystem.update(deltaClock.getElapsedTime().asSeconds());

    sf::Vector2f velocity(0, 0);
    if (controls[UP])
    {
        velocity.y -= action == "Swimming" ? 10 : action == "Burning" ? 2 : 3;
    }
    if (controls[DOWN])
    {
        velocity.y += action == "Swimming" ? 10 : action == "Burning" ? 2 : 3;
    }
    if (controls[LEFT])
    {
        velocity.x -= action == "Swimming" ? 10 : action == "Burning" ? 2 : 3;
    }
    if (controls[RIGHT])
    {
        velocity.x += action == "Swimming" ? 10 : action == "Burning" ? 2 : 3;
    }

    if (velocity.x != 0 && velocity.y != 0)
    {
        static float hypotenuse = std::sqrt(2) / 2;
        velocity.x = hypotenuse * velocity.x;
        velocity.y = hypotenuse * velocity.y;
    }//

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
            velocity = sf::Vector2f(0, 0);
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
        player.getCharacter().position += velocity;
    }

    if (velocity == sf::Vector2f(0, 0))
    {
        action = "Idle";
    }

    sf::Listener::setPosition(player.getCharacter().position.x, 0, player.getCharacter().position.y);

    camera.setCenter(player.getCharacter().position);

    if (rect.getGlobalBounds().contains(player.getCharacter().position))
    {
        trans.getComponent<CollisionComponent>().onCollision();
    }

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
            player.getInventory().addItem("Dagger");
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

void TestGameState::render()
{
    sf::RenderWindow& window = Global::game.getWindow();
    window.setView(camera);

    mapRenderer.render(window, map);

    characterRenderer.render(window, player.getCharacter());
    characterRenderer.render(window, character);

    window.draw(rect);

    window.draw(torch);

    torch2.getComponent<SpriteComponent>().render(window);

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

    ImGui::Begin("Frame Time");
    std::stringstream ss2;
    float time = frameTime.restart().asSeconds();
    ss2 << "FrameTime: " << time;
    ss2 << "\nFPS: " << 1.0f / time;
    ss2 << "\nTotal Runtime: " << torchClock.getElapsedTime().asSeconds();
    ImGui::Text(ss2.str().c_str());
    ImGui::End();
}

void TestGameState::cleanup()
{

}

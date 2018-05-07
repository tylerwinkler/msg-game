#include <cmath>
#include <iostream>
#include <sstream>
#include <thread>

#include "SFML/Audio/Listener.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#include "SFML/Network/IpAddress.hpp"
#include "SFML/Network/Packet.hpp"
#include "SFML/Network/TcpSocket.hpp"

#include "SFML/System/Clock.hpp"

#include "SFML/Window/Event.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

#include "Entities/EntityFactory.hpp"
#include "CharacterRenderer.hpp"

#include "Tilemap/TileMap.hpp"
#include "Tilemap/TileMapRenderer.hpp"
#include "Tilemap/TileMapSerializer.hpp"

#include "Components/AnimationComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/ComponentFactory.hpp"

#include "Console.hpp"
#include "IMouseEventListener.hpp"
#include "Player.hpp"
#include "TextureManager.hpp"
#include "TilemapEditor.hpp"

#include "Global.hpp"
#include "GameEngine.hpp"

int main(int argc, char* argv[])
{
    Console console;
    console.close();

    const int CanSwim = false;

    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600, 32), "MSG");
    window.setFramerateLimit(80);
    window.setVerticalSyncEnabled(false);

    ImGui::SFML::Init(window);

    TileMapSerializer serializer;

    TileMap map = serializer.deserialize("./assets/maps/edana.txt");

    sf::Texture& atlas = Global::game.getTextureManager().get("./assets/images/atlas.jpg");

    Player player;
    player.getCharacter() = EntityFactory::createCharacter(0);
    player.getCharacter().position = sf::Vector2f(150, 150);

    float& health = ((HealthComponent&)player.getCharacter().getComponentByType(ComponentType::HealthComponent)).hp;
    TileMapRenderer mapRenderer;
    mapRenderer.setTileAtlas(atlas);

    Tile* selectedTile = nullptr;

    CharacterRenderer characterRenderer;
    characterRenderer.setCircle(10, sf::Color::Blue);

    enum Movement {UP, DOWN, LEFT, RIGHT};
    bool controls[] = {false, false, false, false};

    sf::View camera;
    camera.setCenter(player.getCharacter().position);
    camera.setSize(window.getView().getSize());

    std::string action = "Idle";

    Entity trans = EntityFactory::createMapTransition(0);
    trans.position = sf::Vector2f(400, 400);
    CollisionComponent& comp = dynamic_cast<CollisionComponent&>(trans.getComponentByType(ComponentType::CollisionComponent));

    sf::RectangleShape rect;
    rect.setPosition(trans.position.x + comp.x, trans.position.y + comp.y);
    rect.setSize(sf::Vector2f(comp.width, comp.height));
    rect.setFillColor(sf::Color(200, 0, 0, 150));
    rect.setOutlineColor(sf::Color(200, 0, 0, 250));
    rect.setOutlineThickness(5.f);

    comp.setCollisionFunc([&]{
                            map = serializer.deserialize("./assets/maps/map.txt");
                            trans.position = sf::Vector2f(0, 0);
                            rect.setPosition(trans.position.x + comp.x, trans.position.y + comp.y);
                          });

    sf::Clock deltaClock;
    sf::Clock frameTime;

    bool running = true;

    console.setFunction("exit", [&]{running = false;});
    console.setFunction("rosebud", [&]{player.getWallet().addGold(1000);});
    console.setFunction("respawn", [&]{health = 1.f; player.getCharacter().position = sf::Vector2f(150, 150);});
    console.setFunction("loadmap map", [&]{map = serializer.deserialize("./assets/maps/map.txt");});
    console.setFunction("loadmap edana", [&]{map = serializer.deserialize("./assets/maps/edana.txt");});

    std::vector<IMouseEventListener*> mouseListeners;
    TilemapEditor editor;
    mouseListeners.push_back(&editor);

    sf::Texture& unlitTorchTxr = Global::game.getTextureManager().get("./assets/images/torch-unlit.png");
    sf::Texture& litTorchTxr = Global::game.getTextureManager().get("./assets/images/torch-lit.png");

    sf::Sprite torch;
    torch.setTexture(unlitTorchTxr);

    torch.setPosition(sf::Vector2f(300, 300));

    bool torchLit = false;

    sf::Texture torchLight = Global::game.getTextureManager().get("./assets/images/torch-light.png");
    sf::Sprite light;
    light.setTexture(torchLight);
    light.setPosition(sf::Vector2f(300, 300));
    light.setOrigin(256 - torch.getOrigin().x, 256 - torch.getOrigin().y);
    light.setColor(sf::Color(200, 150, 100));

    sf::RenderTexture lightmap;
    lightmap.create(map.getWidth() * 64, map.getHeight() * 64);
    sf::RectangleShape blackbox;
    blackbox.setSize(sf::Vector2f(map.getWidth() * 64, map.getHeight() * 64));
    blackbox.setFillColor(sf::Color(10, 10, 10));

    bool lightControl = false;

    sf::Clock torchClock;
    float seconds = -3.f;

    sf::Sprite lightmapSprite;

    sf::SoundBuffer buffer;
    buffer.loadFromFile("./assets/sound/waterfall_.ogg");

    sf::Sound sound;
    sound.setBuffer(buffer);

    sound.setPosition(300.f, 0.f, 300.f);
    sound.setVolume(0.3f);
    sound.setLoop(true);
    sound.play();

    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            switch (event.type)
            {
            case sf::Event::Closed:
                running = false;
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
                    continue;
                }
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                    controls[UP] = true;
                    break;
                case sf::Keyboard::S:
                    controls[DOWN] = true;
                    break;
                case sf::Keyboard::A:
                    controls[LEFT] = true;
                    break;
                case sf::Keyboard::D:
                    controls[RIGHT] = true;
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

        ImGui::SFML::Update(window, deltaClock.restart());

        sf::Vector2f velocity(0, 0);
        if (controls[UP])
        {
            velocity.y -= action == "Swimming" ? 10 : action == "Burning" ? 2 : 5;
        }
        if (controls[DOWN])
        {
            velocity.y += action == "Swimming" ? 10 : action == "Burning" ? 2 : 5;
        }
        if (controls[LEFT])
        {
            velocity.x -= action == "Swimming" ? 10 : action == "Burning" ? 2 : 5;
        }
        if (controls[RIGHT])
        {
            velocity.x += action == "Swimming" ? 10 : action == "Burning" ? 2 : 5;
        }

        if (velocity.x != 0 && velocity.y != 0)
        {
            static float sqrt2 = std::sqrt(2);
            velocity.x = sqrt2 / 2 * velocity.x;
            velocity.y = sqrt2 / 2 * velocity.y;
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
                velocity = sf::Vector2f(0, 0);
            }
            break;
        case Tile::LAVA:
            action = "Burning";
            health -= 0.01f;
            break;
        default:
            action = "Walking";
            break;
        }

        if (health > 0.0)
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
            comp.onCollision();
        }

        if (torch.getGlobalBounds().contains(player.getCharacter().position))
        {
            if (torchClock.getElapsedTime().asSeconds() >= seconds + 3)
            {
                if (!torchLit)
                {
                    torch.setTexture(litTorchTxr);
                }
                else
                {
                    torch.setTexture(unlitTorchTxr);
                }
                torchLit = !torchLit;
                seconds = torchClock.getElapsedTime().asSeconds();
            }

        }

        // Player stats
        ImGui::Begin("");
        ImGui::Text(std::string("Status: " + action).c_str());
        if (health > 0.0)
        {
            const int maxhealth = 150;
            float hp = health * maxhealth;
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

        window.clear();
        window.setView(camera);

        mapRenderer.render(window, map);

        characterRenderer.render(window, player.getCharacter());

        window.draw(rect);

        window.draw(torch);

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

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

    window.close();

    return 0;
}

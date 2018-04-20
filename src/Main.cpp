#include <cmath>
#include <iostream>
#include <sstream>
#include <thread>

#include "SFML/Graphics/RenderWindow.hpp"

#include "SFML/Network/IpAddress.hpp"
#include "SFML/Network/Packet.hpp"
#include "SFML/Network/TcpSocket.hpp"

#include "SFML/System/Clock.hpp"

#include "SFML/Window/Event.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

#include "Character.hpp"
#include "CharacterRenderer.hpp"

#include "TileMap.hpp"
#include "TileMapRenderer.hpp"
#include "TileMapSerializer.hpp"

#include "Components/AnimationComponent.hpp"
#include "Components/SpriteComponent.hpp"

int main(int argc, char* argv[])
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600, 32), "MSG");
    window.setFramerateLimit(80);

    ImGui::SFML::Init(window);

    TileMapSerializer serializer;

    TileMap map = serializer.deserialize("./assets/maps/edana.txt");

    sf::Texture atlas;
    if (!atlas.loadFromFile("./assets/images/atlas.jpg"))
    {
        return 1;
    }

    TileMapRenderer mapRenderer;
    mapRenderer.setTileAtlas(atlas);

    Tile* selectedTile = nullptr;

    Character character;
    character.position = sf::Vector2f(150, 150);
    CharacterRenderer characterRenderer;
    characterRenderer.setCircle(10, sf::Color::Blue);

    std::unique_ptr<Component> animationComponent(new AnimationComponent);
    character.addComponent(animationComponent);

    std::unique_ptr<Component> spriteComponent(new SpriteComponent);
    character.addComponent(spriteComponent);

    if (!character.init())
    {
        return 1;
    }

    enum Movement {UP, DOWN, LEFT, RIGHT};
    bool controls[] = {false, false, false, false};

    sf::View camera;
    camera.setCenter(character.position);
    camera.setSize(window.getView().getSize());

    float health = 1.0;

    std::string action = "Idle";

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                camera.setSize(event.size.width, event.size.height);
                break;
            case sf::Event::MouseButtonPressed:
                if (ImGui::IsAnyItemHovered())
                {
                    break;
                }
                selectedTile = &map.raytrace(
                                             window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), camera).x,
                                              window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), camera).y);
                break;
            case sf::Event::KeyPressed:
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

        sf::Vector2f destination = character.position + velocity;

        int id = map.raytrace(destination.x, destination.y).id;

        switch (id)
        {
        case Tile::WATER:
            action = "Swimming";
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
            character.position += velocity;
        }

        if (velocity == sf::Vector2f(0, 0))
        {
            action = "Idle";
        }

        camera.setCenter(character.position);

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

        window.clear();
        window.setView(camera);

        mapRenderer.render(window, map);

        characterRenderer.render(window, character);

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}

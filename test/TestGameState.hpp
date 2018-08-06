#ifndef MSG_GAME_TEST_TESTGAMESTATE_HPP
#define MSG_GAME_TEST_TESTGAMESTATE_HPP

#include "State.hpp"

#include <cmath>
#include <sstream>

#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Audio/Listener.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"

#include "SFML/System/Clock.hpp"

#include "Components/AnimationComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/HealthComponent.hpp"

#include "Entities/EntityFactory.hpp"

#include "Systems/AnimationSystem.hpp"

#include "Tilemap/TileMapRenderer.hpp"
#include "Tilemap/TileMapSerializer.hpp"

#include "UI/BankWindow.hpp"
#include "UI/DialogWindow.hpp"
#include "UI/LootWindow.hpp"

#include "CharacterRenderer.hpp"
#include "Console.hpp"
#include "GameEngine.hpp"
#include "Global.hpp"
#include "IMouseEventListener.hpp"
#include "Player.hpp"
#include "TextureManager.hpp"
#include "TilemapEditor.hpp"

#include "TmxLoader.hpp"

class TestGameState : public State
{
public:
    bool init() final override;

    void onResize(int width, int height) final override;

    void onMouseButton(int x, int y, int button, bool pressed) final override;

    void onMouseWheelMoved(float delta) final override;

    void onKey(int keyCode, bool control, bool alt, bool shift, bool system, bool pressed) final override;

    void update() final override;

    void render(float interpolation) final override;

    void cleanup() final override;

    void imguiUpdate() final override;

public:
    sf::View ui;
    sf::View camera;
    std::vector<IMouseEventListener*> mouseListeners;
    Console console;

    enum Movement {UP, DOWN, LEFT, RIGHT};
    Player player;
    bool torchLit = false;
    bool lightControl = false;
    sf::Clock deltaClock;
    std::string action = "Idle";
    TileMap map;
    const int CanSwim = false;
    sf::RectangleShape rect;
    sf::Sprite torch;
    int transID;
    int torch2ID;
    int chestID;
    sf::Clock frameTime;
    sf::Clock torchClock;
    float seconds = -3.f;
    Tile* selectedTile = nullptr;
    TileMapRenderer mapRenderer;
    TileMapSerializer serializer;
    CharacterRenderer characterRenderer;
    sf::RenderTexture lightmap;
    sf::Sprite lightmapSprite;
    sf::RectangleShape blackbox;
    sf::Sprite light;
    TilemapEditor editor;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    bool m_interact;
    bool m_sprint;
    TmxMap map2;
    LootWindow lootWin;
    DialogWindow diagWin;

    BankWindow bankWin;

    int incrementer;

    int trees[200];
}; // TestGameState

#endif // MSG_GAME_TEST_TESTGAMESTATE_HPP

#include "GameEngine.hpp"

#include <iostream>

#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Graphics/RenderWindow.hpp"

#include "Systems/AnimationSystem.hpp"
#include "Systems/CollisionSystem.hpp"
#include "Systems/EntitySystem.hpp"

#include "FontManager.hpp"
#include "State.hpp"
#include "StateMachine.hpp"
#include "TextureManager.hpp"

GameEngine::GameEngine() : m_running(false), m_window(new sf::RenderWindow),
    m_fontManager(new FontManager), m_stateMachine(new StateMachine),
    m_textureManager(new TextureManager),m_animationSystem(new AnimationSystem),
    m_collisionSystem(new CollisionSystem), m_entitySystem(new EntitySystem)
{
    m_window->create(sf::VideoMode(800, 600, 32), "My SFML Game");

    ImGui::SFML::Init(*m_window);
}

GameEngine::~GameEngine()
{
    delete m_textureManager;
}

void GameEngine::run(State* initialState, int ups)
{
    m_stateMachine->pushState(initialState);

    m_ups = ups;

    m_running = true;

    sf::Clock imguiClock;
    sf::Clock frameClock;

    const int OneSecondMS = 1000;

    int stepInterval = OneSecondMS / ups;

    m_nextUpdate = frameClock.getElapsedTime().asMilliseconds() + stepInterval;

    sf::Vector2f mouseDestination;

    while (m_running)
    {
        State* state = m_stateMachine->getState();

        sf::Event event;
        while (m_window->pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            switch (event.type)
            {
            case sf::Event::Closed:
                quit();
                break;
            case sf::Event::Resized:
                state->onResize(event.size.width, event.size.height);
                break;
            case sf::Event::MouseButtonPressed:
                state->onMouseButton(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button, true);
                break;
            case sf::Event::MouseButtonReleased:
                state->onMouseButton(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button, false);
                break;
            case sf::Event::MouseWheelMoved:
                state->onMouseWheelMoved(event.mouseWheel.delta);
                break;
            case sf::Event::KeyPressed:
                state->onKey(event.key.code, event.key.control, event.key.alt, event.key.shift, event.key.system, true);
                break;
            case sf::Event::KeyReleased:
                state->onKey(event.key.code, event.key.control, event.key.alt, event.key.shift, event.key.system, false);
                break;
            default:
                break;
            }
        }

        int accumulator = 5;
        while (m_nextUpdate <= frameClock.getElapsedTime().asMilliseconds() && accumulator != 0)
        {
            state->update();

            m_nextUpdate += stepInterval;

            --accumulator;
        }
        if (accumulator == 0)
        {
            std::cout << "Game running behind!\n";
        }

        ImGui::SFML::Update(*m_window, imguiClock.restart());
        state->imguiUpdate();

        m_window->clear();

        float interpolation = 1.f - float(frameClock.getElapsedTime().asMilliseconds()) / m_nextUpdate;

        state->render(interpolation);
        ImGui::SFML::Render(*m_window);
        m_window->display();

        if (m_stateMachine->hasPendingStateChange())
        {
            m_stateMachine->processPendingStateChange();
        }
    }

    if (m_stateMachine->getState() != nullptr)
    {
        m_stateMachine->getState()->cleanup();
    }

    ImGui::SFML::Shutdown();
    m_window->close();
}

void GameEngine::quit()
{
    m_running = false;
}

FontManager& GameEngine::getFontManager()
{
    return *m_fontManager;
}

StateMachine& GameEngine::getStateMachine()
{
    return *m_stateMachine;
}

TextureManager& GameEngine::getTextureManager()
{
    return *m_textureManager;
}

sf::RenderWindow& GameEngine::getWindow()
{
    return *m_window;
}

AnimationSystem& GameEngine::getAnimationSystem()
{
    return *m_animationSystem;
}

CollisionSystem& GameEngine::getCollisionSystem()
{
    return *m_collisionSystem;
}

EntitySystem& GameEngine::getEntitySystem()
{
    return *m_entitySystem;
}

int GameEngine::getUPS()
{
    return m_ups;
}

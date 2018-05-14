#include "GameEngine.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

#include "State.hpp"
#include "StateMachine.hpp"
#include "TextureManager.hpp"

GameEngine::GameEngine() : m_running(false), m_window(), m_stateMachine(new StateMachine), m_textureManager(new TextureManager)
{
    m_window.create(sf::VideoMode(800, 600, 32), "My SFML Game");

    ImGui::SFML::Init(m_window);
}

GameEngine::~GameEngine()
{
    delete m_textureManager;
}

void GameEngine::run(State* initialState)
{
    m_stateMachine->pushState(initialState);

    m_running = true;

    sf::Clock frameClock;
    while (m_running)
    {
        State* state = m_stateMachine->getState();

        sf::Event event;
        while (m_window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            state->handleEvent(event);
        }

        ImGui::SFML::Update(m_window, frameClock.restart());
        state->update();

        m_window.clear();
        state->render();
        ImGui::SFML::Render(m_window);
        m_window.display();

        if (m_stateMachine->hasPendingStateChange())
        {
            m_stateMachine->processPendingStateChange();
        }
    }
    ImGui::SFML::Shutdown();
    m_window.close();
}

void GameEngine::quit()
{
    m_running = false;
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
    return m_window;
}

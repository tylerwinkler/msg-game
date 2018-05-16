#include "States/MainMenuState.hpp"

#include "FontManager.hpp"
#include "GameEngine.hpp"
#include "Global.hpp"
#include "StateMachine.hpp"

bool MainMenuState::init()
{
    m_text.setFont(Global::game.getFontManager().get("assets/fonts/font.ttf"));
    m_text1.setFont(Global::game.getFontManager().get("assets/fonts/font.ttf"));
    m_text2.setFont(Global::game.getFontManager().get("assets/fonts/font.ttf"));
    m_text3.setFont(Global::game.getFontManager().get("assets/fonts/font.ttf"));

    m_text.setString("MAIN MENU");
    m_text1.setString("New Game");
    m_text2.setString("Load Game");
    m_text3.setString("Fuck Off");

    m_text.setPosition(sf::Vector2f(100, 100));
    m_text1.setPosition(sf::Vector2f(120, 140));
    m_text2.setPosition(sf::Vector2f(140, 180));
    m_text3.setPosition(sf::Vector2f(160, 220));

    return true;
}

void MainMenuState::onMouseButton(int x, int y, int button, bool pressed)
{
    if (pressed)
    {
        if (m_text1.getGlobalBounds().contains(x, y))
        {
            //Global::game.getStateMachine().changeState(new PlayGameState);
        }
        if (m_text2.getGlobalBounds().contains(x, y))
        {
            //Global::game.getStateMachine().changeState(new PlayGameState);
        }
        if (m_text3.getGlobalBounds().contains(x, y))
        {
            Global::game.quit();
        }
    }
}

void MainMenuState::onKey(int keyCode, bool control, bool alt, bool shift, bool system, bool pressed)
{

}

void MainMenuState::update()
{

}

void MainMenuState::render()
{
    Global::game.getWindow().draw(m_text);
    Global::game.getWindow().draw(m_text1);
    Global::game.getWindow().draw(m_text2);
    Global::game.getWindow().draw(m_text3);
}

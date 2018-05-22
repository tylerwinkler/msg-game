#include "States/MainMenuState.hpp"

#include "SFML/Graphics/RenderWindow.hpp"

#include "States/LoadGameState.hpp"
#include "States/NewGameState.hpp"
#include "States/OptionsState.hpp"

#include "FontManager.hpp"
#include "GameEngine.hpp"
#include "Global.hpp"
#include "StateMachine.hpp"
#include "TextureManager.hpp"

bool MainMenuState::init()
{
    m_background.setTexture(Global::game.getTextureManager().get("./assets/images/background.jpg"));

    m_menuHeader.setFont(Global::game.getFontManager().get("assets/fonts/font.ttf"));
    m_newGameText.setFont(Global::game.getFontManager().get("assets/fonts/font.ttf"));
    m_loadGameText.setFont(Global::game.getFontManager().get("assets/fonts/font.ttf"));
    m_optionsText.setFont(Global::game.getFontManager().get("assets/fonts/font.ttf"));
    m_exitText.setFont(Global::game.getFontManager().get("assets/fonts/font.ttf"));

    m_menuHeader.setString("MAIN MENU");
    m_newGameText.setString("New Game");
    m_loadGameText.setString("Load Game");
    m_optionsText.setString("Options");
    m_exitText.setString("Quit Game");

    m_menuHeader.setPosition(sf::Vector2f(100, 100));
    m_newGameText.setPosition(sf::Vector2f(120, 140));
    m_loadGameText.setPosition(sf::Vector2f(140, 180));
    m_optionsText.setPosition(sf::Vector2f(160, 220));
    m_exitText.setPosition(sf::Vector2f(180, 260));

    m_menuHeader.setColor(sf::Color::Black);
    m_newGameText.setColor(sf::Color::Black);
    m_loadGameText.setColor(sf::Color::Black);
    m_optionsText.setColor(sf::Color::Black);
    m_exitText.setColor(sf::Color::Black);

    return true;
}

void MainMenuState::onMouseButton(int x, int y, int button, bool pressed)
{
    if (pressed)
    {
        if (m_newGameText.getGlobalBounds().contains(x, y))
        {
            Global::game.getStateMachine().changeState(new NewGameState);
        }
        if (m_loadGameText.getGlobalBounds().contains(x, y))
        {
            Global::game.getStateMachine().changeState(new LoadGameState);
        }
        if (m_optionsText.getGlobalBounds().contains(x, y))
        {
            Global::game.getStateMachine().changeState(new OptionsState);
        }
        if (m_exitText.getGlobalBounds().contains(x, y))
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
    Global::game.getWindow().draw(m_background);
    Global::game.getWindow().draw(m_menuHeader);
    Global::game.getWindow().draw(m_newGameText);
    Global::game.getWindow().draw(m_loadGameText);
    Global::game.getWindow().draw(m_optionsText);
    Global::game.getWindow().draw(m_exitText);
}

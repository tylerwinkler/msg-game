#include "States/NewGameState.hpp"

#include "SFML/Graphics/RenderWindow.hpp"

#include "States/MainMenuState.hpp"

#include "FontManager.hpp"
#include "GameEngine.hpp"
#include "Global.hpp"
#include "StateMachine.hpp"
#include "TextureManager.hpp"

bool NewGameState::init()
{
    m_background.setTexture(Global::game.getTextureManager().get("./assets/images/background.jpg"));

    m_menuHeader.setFont(Global::game.getFontManager().get("assets/fonts/font.ttf"));
    m_backText.setFont(Global::game.getFontManager().get("assets/fonts/font.ttf"));

    m_menuHeader.setString("NEW GAME");
    m_backText.setString("Back");

    m_menuHeader.setPosition(sf::Vector2f(100, 100));
    m_backText.setPosition(sf::Vector2f(120, 140));

    m_menuHeader.setFillColor(sf::Color::Black);
    m_backText.setFillColor(sf::Color::Black);

    return true;
}

void NewGameState::onMouseButton(int x, int y, int button, bool pressed)
{
    if (pressed)
    {
        if (m_backText.getGlobalBounds().contains(x, y))
        {
            Global::game.getStateMachine().changeState(new MainMenuState);
        }
    }
}

void NewGameState::onKey(int keyCode, bool control, bool alt, bool shift, bool system, bool pressed)
{

}

void NewGameState::update()
{

}

void NewGameState::render(float interpolation)
{
    Global::game.getWindow().draw(m_background);
    Global::game.getWindow().draw(m_menuHeader);
    Global::game.getWindow().draw(m_backText);
}

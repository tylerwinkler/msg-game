#include "UI/DialogWindow.hpp"

#include "FontManager.hpp"
#include "GameEngine.hpp"
#include "Global.hpp"

DialogWindow::DialogWindow()
{
    m_speaker.setFont(Global::game.getFontManager().get("./assets/fonts/font.ttf"));
    m_text.setFont(Global::game.getFontManager().get("./assets/fonts/font.ttf"));

    m_rect.setSize(sf::Vector2f(480, 240));
    m_rect.setFillColor(sf::Color::Black);

    m_rect.setPosition(200, 200);

    m_text.setPosition(m_rect.getPosition());
    m_text.move(10, 40);
}

void DialogWindow::open(DialogComponent& dialog)
{
    ((Frame*)this)->open();

    m_speaker.setString("Josh");
    m_text.setString("I suck at league!");

    alignSpeakerText();
    cropText();
}

void DialogWindow::onRender(sf::RenderTarget& target)
{
    target.draw(m_rect);
    target.draw(m_speaker);
    target.draw(m_text);
}

void DialogWindow::alignSpeakerText()
{
    m_speaker.setOrigin(m_speaker.getGlobalBounds().width / 2, m_speaker.getGlobalBounds().height / 2);

    m_speaker.setPosition(int(m_rect.getPosition().x + m_rect.getGlobalBounds().width / 2), m_rect.getPosition().y);
}

void DialogWindow::cropText()
{
    const int ContainerPadding = 20;

    sf::String str = m_text.getString();

    for (size_t i = 0; i < str.getSize(); ++i)
    {

    }
}

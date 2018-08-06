#include "UI/BankWindow.hpp"

#include "Components/BankComponent.hpp"

#include "FontManager.hpp"
#include "GameEngine.hpp"
#include "Global.hpp"

BankWindow::BankWindow()
{
    m_rect.setPosition(100, 200);
    m_rect.setSize(sf::Vector2f(400, 700));

    m_rect.setFillColor(sf::Color(20, 40, 80));
    m_rect.setOutlineColor(sf::Color(100, 60, 0));
    m_rect.setOutlineThickness(2.f);

    m_header.setFont(Global::game.getFontManager().get("./assets/fonts/font.ttf"));
    m_header.setCharacterSize(18);
    m_header.setPosition(m_rect.getPosition().x + 80, m_rect.getPosition().y + 15);
    m_header.setFillColor(sf::Color::White);
    m_header.setString("Bank");
}

void BankWindow::open(BankComponent& bankComponent)
{
    int index = 0;
    for (auto item : bankComponent.items)
    {
        sf::Text text;
        text.setFont(Global::game.getFontManager().get("./assets/fonts/font.ttf"));
        text.setCharacterSize(14);
        text.setPosition(m_rect.getPosition().x + 10, m_rect.getPosition().y + 30 + 15 * ++index);
        text.setFillColor(sf::Color::White);
        text.setString(item);

        m_items.push_back(text);
    }

    ((Frame*)this)->open();
}

void BankWindow::onRender(sf::RenderTarget& target)
{
    target.draw(m_rect);
    target.draw(m_header);

    for (auto item : m_items)
    {
        target.draw(item);
    }
}


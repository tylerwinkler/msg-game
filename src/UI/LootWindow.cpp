#include "UI/LootWindow.hpp"

#include "Components/LootComponent.hpp"

#include "FontManager.hpp"
#include "GameEngine.hpp"
#include "Global.hpp"

LootWindow::LootWindow()
{
    m_frame.setSize(sf::Vector2f(200, 300));
    m_frame.setFillColor(sf::Color(23, 90, 150, 200));
    m_frame.setOutlineColor(sf::Color(23, 90, 150, 250));
    m_frame.setOutlineThickness(1.f);
    m_frame.setPosition(250, 250);

    m_header.setFont(Global::game.getFontManager().get("./assets/fonts/font.ttf"));
    m_lootAllText.setFont(Global::game.getFontManager().get("./assets/fonts/font.ttf"));

    m_header.setString("Chest Loot");
    m_header.setCharacterSize(20);
    m_header.setPosition(int(m_frame.getPosition().x + 10), int(m_frame.getPosition().y + 10));

    m_lootAll.setSize(sf::Vector2f(90, 30));
    m_lootAll.setFillColor(sf::Color(23, 90, 150, 255));
    m_lootAll.setOutlineColor(sf::Color(23, 90, 250, 250));
    m_lootAll.setOutlineThickness(1.f);
    m_lootAll.setPosition(int(m_frame.getPosition().x + m_frame.getGlobalBounds().width / 2), int(m_frame.getPosition().y + m_frame.getGlobalBounds().height - 40));

    m_lootAllText.setString("Loot All");
    m_lootAllText.setCharacterSize(16);
    m_lootAllText.setPosition(int(m_frame.getPosition().x + m_frame.getGlobalBounds().width / 2), int(m_frame.getPosition().y + m_frame.getGlobalBounds().height - 40));
}

void LootWindow::open(LootComponent& loot)
{
    ((Frame*)this)->open();

    m_lootContents.clear();

    m_loot = &loot;

    std::vector<int>& items = m_loot->getItems();

    int count = 0;
    for (auto& item : items)
    {
        sf::Text text;
        text.setFont(Global::game.getFontManager().get("./assets/fonts/font.ttf"));
        text.setString("Dagger");
        text.setCharacterSize(16);
        text.setPosition(m_frame.getPosition().x + 10, m_frame.getPosition().y + 50 + 20 * count);

        m_lootContents.push_back(text);

        ++count;
    }
}

void LootWindow::onRender(sf::RenderTarget& target)
{
    target.draw(m_frame);
    target.draw(m_header);

    for (auto& item : m_lootContents)
    {
        target.draw(item);
    }

    target.draw(m_lootAll);
    target.draw(m_lootAllText);
}

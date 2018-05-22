#include "UI/LootWindow.hpp"

#include "Components/LootComponent.hpp"

#include "FontManager.hpp"
#include "GameEngine.hpp"
#include "Global.hpp"

LootWindow::LootWindow()
{
    m_open = false;

    m_frame.setSize(sf::Vector2f(200, 300));
    m_frame.setFillColor(sf::Color(23, 90, 150, 200));
    m_frame.setOutlineColor(sf::Color(23, 90, 150, 250));
    m_frame.setOutlineThickness(1.f);
    m_frame.setPosition(250, 250);
}

void LootWindow::open(LootComponent& loot)
{
    m_open = true;

    m_loot = &loot;

    std::vector<int>& items = m_loot->getItems();

    int count = 0;
    for (auto& item : items)
    {
        sf::Text text;
        text.setFont(Global::game.getFontManager().get("./assets/fonts/font.ttf"));
        text.setString("Dagger");
        text.setCharacterSize(16);
        text.setPosition(m_frame.getPosition().x + 10, m_frame.getPosition().y + 10 + 20 * count);

        m_lootContents.push_back(text);

        ++count;
    }
}

void LootWindow::close()
{
    m_open = false;

    m_loot = nullptr;

    m_lootContents.clear();
}

void LootWindow::render(sf::RenderTarget& target)
{
    if (!m_open)
    {
        return;
    }

    target.draw(m_frame);

    for (auto& item : m_lootContents)
    {
        target.draw(item);
    }
}

#ifndef MSG_GAME_UI_LOOTWINDOW_HPP
#define MSG_GAME_UI_LOOTWINDOW_HPP

#include <vector>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Text.hpp"

class LootComponent;

class LootWindow
{
public:
    LootWindow();

public:
    void open(LootComponent& loot);

    void close();

    void render(sf::RenderTarget& target);

private:
    bool m_open;

    sf::RectangleShape m_frame;

    std::vector<sf::Text> m_lootContents;

    LootComponent* m_loot;
}; // LootWindow

#endif // MSG_GAME_UI_LOOTWINDOW_HPP

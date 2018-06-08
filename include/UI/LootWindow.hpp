#ifndef MSG_GAME_UI_LOOTWINDOW_HPP
#define MSG_GAME_UI_LOOTWINDOW_HPP

#include <vector>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Text.hpp"

#include "UI/Frame.hpp"

class LootComponent;

class LootWindow : public Frame
{
public:
    LootWindow();

public:
    void open(LootComponent& loot);

    void onRender(sf::RenderTarget& target);

private:
    sf::RectangleShape m_frame;

    sf::Text m_header;
    std::vector<sf::Text> m_lootContents;

    sf::RectangleShape m_lootAll;
    sf::Text m_lootAllText;

    LootComponent* m_loot;
}; // LootWindow

#endif // MSG_GAME_UI_LOOTWINDOW_HPP

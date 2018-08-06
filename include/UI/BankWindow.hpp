#ifndef MSG_GAME_UI_BANKWINDOW_HPP
#define MSG_GAME_UI_BANKWINDOW_HPP

#include <vector>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

#include "UI/Frame.hpp"

namespace sf { class RenderWindow; }

class BankComponent;

class BankWindow : public Frame
{
public:
    BankWindow();

public:
    void open(BankComponent& bankComponent);

    void onRender(sf::RenderTarget& target) override;

private:
    sf::RectangleShape m_rect;

    sf::Text m_header;

    std::vector<sf::Text> m_items;
};

#endif // MSG_GAME_UI_BANKWINDOW_HPP

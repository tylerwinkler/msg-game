#ifndef MSG_GAME_UI_DIALOGWINDOW_HPP
#define MSG_GAME_UI_DIALOGWINDOW_HPP

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

#include "UI/Frame.hpp"

class DialogComponent;

class DialogWindow : public Frame
{
public:
    DialogWindow();

public:
    void open(DialogComponent& dialog);

    void onRender(sf::RenderTarget& target) final override;

private:
    void alignSpeakerText();
    void cropText();

private:
    sf::Text m_speaker;
    sf::Text m_text;
    sf::RectangleShape m_rect;
}; // DialogWindow

#endif // MSG_GAME_UI_DIALOGWINDOW_HPP

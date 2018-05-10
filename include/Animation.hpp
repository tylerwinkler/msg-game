#ifndef MSG_GAME_ANIMATION_HPP
#define MSG_GAME_ANIMATION_HPP

#include <string>
#include <vector>

#include "SFML/Graphics/Rect.hpp"

struct Animation
{
    std::vector<sf::IntRect> frames;
    float animationTime;

    void loadFromFile(const std::string& filename);
}; // Animation

#endif // MSG_GAME_ANIMATION_HPP

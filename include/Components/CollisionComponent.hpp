#ifndef MSG_GAME_COMPONENTS_COLLISIONCOMPONENT_HPP
#define MSG_GAME_COMPONENTS_COLLISIONCOMPONENT_HPP

#include <functional>

#include "SFML/Graphics/Rect.hpp"

#include "Components/Component.hpp"

class CollisionComponent : public Component
{
public:
    CollisionComponent();
    CollisionComponent(int x, int y, int width, int height);

public:
    sf::IntRect rect;

public:
    bool onInit(Entity* owner);

    void setCollisionFunc(std::function<void(Entity&)> func);

    void onCollision(Entity& other);

    void receive(int x, int y);

private:
    std::function<void(Entity&)> m_collisionFunc;
}; // CollisionComponent

#endif // MSG_GAME_COMPONENTS_COLLISIONCOMPONENT_HPP

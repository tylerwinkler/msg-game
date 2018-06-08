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
    int offsetX;
    int offsetY;
    bool trigger;

public:
    bool onInit(int ownerID);

    void setCollisionFunc(std::function<void(CollisionComponent&)> func);

    void onCollision(CollisionComponent& other);

    void receive(int x, int y);

private:
    std::function<void(CollisionComponent&)> m_collisionFunc;
}; // CollisionComponent

#endif // MSG_GAME_COMPONENTS_COLLISIONCOMPONENT_HPP

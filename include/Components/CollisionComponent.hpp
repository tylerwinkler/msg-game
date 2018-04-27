#ifndef MSG_GAME_COMPONENTS_COLLISIONCOMPONENT_HPP
#define MSG_GAME_COMPONENTS_COLLISIONCOMPONENT_HPP

#include <functional>

#include "Components/Component.hpp"

class CollisionComponent : public Component
{
public:
    CollisionComponent();
    CollisionComponent(int x, int y, int width, int height);

public:
    int x;
    int y;
    int width;
    int height;

public:
    void setCollisionFunc(std::function<void()> func);

    void onCollision();

private:
    std::function<void()> m_collisionFunc;
}; // CollisionComponent

#endif // MSG_GAME_COMPONENTS_COLLISIONCOMPONENT_HPP

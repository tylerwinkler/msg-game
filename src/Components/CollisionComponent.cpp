#include "Components/CollisionComponent.hpp"

CollisionComponent::CollisionComponent() : CollisionComponent(0, 0, 0, 0)
{
}

CollisionComponent::CollisionComponent(int x, int y, int width, int height)
{
    type = ComponentType::CollisionComponent;

    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void CollisionComponent::setCollisionFunc(std::function<void()> func)
{
    m_collisionFunc = func;
}

void CollisionComponent::onCollision()
{
    if (m_collisionFunc != nullptr)
    m_collisionFunc();
}

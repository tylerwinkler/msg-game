#include "Components/CollisionComponent.hpp"


void CollisionComponent::setCollisionFunc(std::function<void()> func)
{
    m_collisionFunc = func;
}

void CollisionComponent::onCollision()
{
    m_collisionFunc();
}

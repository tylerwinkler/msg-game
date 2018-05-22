#include "Components/CollisionComponent.hpp"

#include "Entities/Entity.hpp"

#include <iostream>

CollisionComponent::CollisionComponent() : CollisionComponent(0, 0, 0, 0)
{
}

CollisionComponent::CollisionComponent(int x, int y, int width, int height)
{
    type = ComponentType::CollisionComponent;

    rect = sf::IntRect(x, y, width, height);

    m_collisionFunc = nullptr;
}

bool CollisionComponent::onInit(Entity* owner)
{
    owner->addObserver(this);
    std::cout << "CollisionComponent Listening\n";
    return true;
}

void CollisionComponent::setCollisionFunc(std::function<void(Entity&)> func)
{
    m_collisionFunc = std::move(func);
}

void CollisionComponent::onCollision(Entity& other)
{
    std::cout << "Colliding!\n";
    if (m_collisionFunc != nullptr)
    {
        m_collisionFunc(other);
    }
}

void CollisionComponent::receive(int x, int y)
{
    rect.left = x;
    rect.top = y;
}

#include "Components/CollisionComponent.hpp"

#include "Entities/Entity.hpp"

#include "Systems/EntitySystem.hpp"

#include "GameEngine.hpp"
#include "Global.hpp"

CollisionComponent::CollisionComponent() : CollisionComponent(0, 0, 0, 0)
{
}

CollisionComponent::CollisionComponent(int x, int y, int width, int height)
{
    type = ComponentType::CollisionComponent;

    rect = sf::IntRect(x, y, width, height);

    offsetX = x;
    offsetY = y;

    trigger = false;

    m_collisionFunc = nullptr;
}

bool CollisionComponent::onInit(int ownerID)
{
    Global::game.getEntitySystem().getEntity(ownerID).addObserver(this);

    return true;
}

void CollisionComponent::setCollisionFunc(std::function<void(CollisionComponent&)> func)
{
    m_collisionFunc = std::move(func);
}

void CollisionComponent::onCollision(CollisionComponent& other)
{
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

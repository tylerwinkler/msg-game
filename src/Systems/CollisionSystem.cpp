#include "Systems/CollisionSystem.hpp"

#include "Components/CollisionComponent.hpp"

#include <iostream>
#include <sstream>

void printBox(CollisionComponent* c)
{
    std::stringstream ss;
    ss << "x: " << c->rect.left
       << "y: " << c->rect.top
       << "w: " << c->rect.width
       << "h: " << c->rect.height;

    std::cout << ss.str() << "\n";
}

void CollisionSystem::update()
{
    if (m_collisionComponents.size() < 2)
    {
        return;
    }

    std::cout << "Updating Collision System\n";

    for (int i = 0; i < m_collisionComponents.size() - 1; ++i)
    {
        for (int j = i + 1; j < m_collisionComponents.size(); ++j)
        {
            CollisionComponent* firstComp = m_collisionComponents[i];
            CollisionComponent* secondComp = m_collisionComponents[j];

            printBox(firstComp);
            printBox(secondComp);
            std::cout << "\n";

            if (firstComp->rect.intersects(secondComp->rect))
            {
                firstComp->onCollision(secondComp->getOwner());
                secondComp->onCollision(firstComp->getOwner());
                std::cout << "Collision!!\n";
            }
        }
    }
}

void CollisionSystem::addComponent(CollisionComponent* comp)
{
    m_collisionComponents.push_back(comp);
}

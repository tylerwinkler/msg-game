#include "Systems/CollisionSystem.hpp"

#include "Components/CollisionComponent.hpp"

#include <iostream>
#include <sstream>

#include "Entities/Entity.hpp"

#include "Systems/EntitySystem.hpp"

#include "GameEngine.hpp"
#include "Global.hpp"

void printBox(CollisionComponent* c)
{
    std::stringstream ss;
    ss << "x: " << c->rect.left
       << "y: " << c->rect.top
       << "w: " << c->rect.width
       << "h: " << c->rect.height;

    std::cout << ss.str() << "\n";
}

void CollisionSystem::prepare()
{
    for (auto& c : m_collisionComponents)
    {
        c.before = c.component->rect;
    }
}

void CollisionSystem::update()
{
    if (m_collisionComponents.size() < 2)
    {
        return;
    }

    for (auto& c : m_collisionComponents)
    {
        c.after = c.component->rect;
    }

    //std::cout << "Updating Collision System\n";

    for (int i = 0; i < m_collisionComponents.size() - 1; ++i)
    {
        for (int j = i + 1; j < m_collisionComponents.size(); ++j)
        {
            CollisionComponent* firstComp = m_collisionComponents[i].component;
            CollisionComponent* secondComp = m_collisionComponents[j].component;

//            printBox(firstComp);
//            printBox(secondComp);
//            std::cout << "\n";

            if (firstComp->rect.intersects(secondComp->rect))
            {
                if (!firstComp->trigger && !secondComp->trigger)
                {
                    Entity& e1 = Global::game.getEntitySystem().getEntity(firstComp->getOwnerID());
                    Entity& e2 = Global::game.getEntitySystem().getEntity(secondComp->getOwnerID());

                    e1.setPosition(m_collisionComponents[i].before.left, m_collisionComponents[i].before.top);
                    e2.setPosition(m_collisionComponents[j].before.left, m_collisionComponents[j].before.top);
                }

                firstComp->onCollision(*secondComp);
                secondComp->onCollision(*firstComp);
                //std::cout << "Collision!!\n";
            }
        }
    }
}

void CollisionSystem::addComponent(CollisionComponent* comp)
{
    CollisionData d;
    d.component = comp;
    d.before = comp->rect;
    d.after = comp->rect;

    m_collisionComponents.push_back(d);
}

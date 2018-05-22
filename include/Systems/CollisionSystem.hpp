#ifndef MSG_GAME_SYSTEMS_COLLISIONSYSTEM_HPP
#define MSG_GAME_SYSTEMS_COLLISIONSYSTEM_HPP

#include <vector>

class CollisionComponent;

class CollisionSystem
{
public:
    void update();

    void addComponent(CollisionComponent* comp);

private:
    // QuadTree m_quadTree;
    std::vector<CollisionComponent*> m_collisionComponents;
}; // CollisionSystem

#endif // MSG_GAME_SYSTEMS_COLLISIONSYSTEM_HPP

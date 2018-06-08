#ifndef MSG_GAME_SYSTEMS_COLLISIONSYSTEM_HPP
#define MSG_GAME_SYSTEMS_COLLISIONSYSTEM_HPP

#include <vector>

#include "SFML/Graphics/Rect.hpp"

class CollisionComponent;

struct CollisionData
{
    CollisionComponent* component;
    sf::IntRect before;
    sf::IntRect after;
};

class CollisionSystem
{
public:
    void prepare();

    void update();

    void addComponent(CollisionComponent* comp);

private:
    // QuadTree m_quadTree;
    std::vector<CollisionData> m_collisionComponents;
}; // CollisionSystem

#endif // MSG_GAME_SYSTEMS_COLLISIONSYSTEM_HPP

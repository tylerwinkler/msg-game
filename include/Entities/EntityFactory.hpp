#ifndef MSG_GAME_ENTITIES_ENTITYFACTORY_HPP
#define MSG_GAME_ENTITIES_ENTITYFACTORY_HPP

#include "Entities/Entity.hpp"

class EntityFactory
{
public:
    static Entity createMapTransition(int transitionId);
}; // EntityFactory

#endif // MSG_GAME_ENTITIES_ENTITYFACTORY_HPP

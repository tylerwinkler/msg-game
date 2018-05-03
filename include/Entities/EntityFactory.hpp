#ifndef MSG_GAME_ENTITIES_ENTITYFACTORY_HPP
#define MSG_GAME_ENTITIES_ENTITYFACTORY_HPP

#include "Entities/Entity.hpp"

class EntityFactory
{
public:
    static Entity createMapTransition(int transitionId);

    static Entity createCharacter(int characterId);
}; // EntityFactory

#endif // MSG_GAME_ENTITIES_ENTITYFACTORY_HPP

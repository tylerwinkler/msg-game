#ifndef MSG_GAME_ENTITIES_ENTITYFACTORY_HPP
#define MSG_GAME_ENTITIES_ENTITYFACTORY_HPP

#include <string>

#include "Entities/Entity.hpp"

class EntityFactory
{
public:
    static Entity create(const std::string& entityType);

    static Entity createMapTransition(int transitionId);

    static Entity createCharacter(int characterId);

    static Entity createTorch();

    static Entity createChest();
}; // EntityFactory

#endif // MSG_GAME_ENTITIES_ENTITYFACTORY_HPP

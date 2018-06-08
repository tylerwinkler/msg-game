#ifndef MSG_GAME_ENTITIES_ENTITYFACTORY_HPP
#define MSG_GAME_ENTITIES_ENTITYFACTORY_HPP

#include <string>

class EntityFactory
{
public:
    static int create(const std::string& entityType);

    static int createMapTransition(int transitionId);

    static int createCharacter(int characterId);

    static int createTorch();

    static int createChest();

    static int createTree();
}; // EntityFactory

#endif // MSG_GAME_ENTITIES_ENTITYFACTORY_HPP

#ifndef MSG_GAME_SYSTEMS_ENTITYSYSTEM_HPP
#define MSG_GAME_SYSTEMS_ENTITYSYSTEM_HPP

#include "Entities/Entity.hpp"

namespace
{
    const int MaxEntities = 256;
}

class EntitySystem
{
public:
    EntitySystem();

    Entity& getEntity(int id);

    Entity& getFreeEntity();

private:
    Entity m_entities[MaxEntities];
    bool m_active[MaxEntities];
};

#endif // MSG_GAME_SYSTEMS_ENTITYSYSTEM_HPP

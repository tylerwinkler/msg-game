#include "Systems/EntitySystem.hpp"

#include <stdexcept>

EntitySystem::EntitySystem()
{
    for (int i = 0; i < MaxEntities; ++i)
    {
        m_active[i] = false;
    }
}

Entity& EntitySystem::getEntity(int id)
{
    return m_entities[id];
}

int EntitySystem::getFreeEntity()
{
    for (int i = 0; i < MaxEntities; ++i)
    {
        if (!m_active[i])
        {
            m_active[i] = true;
            return i;
        }
    }

    throw std::runtime_error("EntitySystem has no free entities left");
}

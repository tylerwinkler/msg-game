#include "Systems/System.hpp"

System::System(GameEngine& engine) : m_engine(engine)
{

}

System::~System()
{

}

GameEngine& System::getEngine()
{
    return m_engine;
}

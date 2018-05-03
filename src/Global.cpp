#include "Global.hpp"

#include "GameEngine.hpp"

namespace
{
    GameEngine implGame;
}

namespace Global
{
    GameEngine& game = implGame;
}

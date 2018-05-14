#include "States/MainMenuState.hpp"

#include "GameEngine.hpp"
#include "Global.hpp"

int main(int argc, char* argv[])
{
    Global::game.run(new MainMenuState);

    return 0;
}

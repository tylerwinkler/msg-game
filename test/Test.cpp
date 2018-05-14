#include "Test.hpp"

#include "GameEngine.hpp"
#include "Global.hpp"
#include "StateMachine.hpp"
#include "TestGameState.hpp"

void Test::fail()
{
    std::cout << "Test failed.\n";
}

void Test::fail(const std::string& message)
{
    std::cout << "Test failed: " << message << "\n";
}

void Test::pass()
{
    std::cout << "Test successful.\n";
}

void Test::pass(const std::string& message)
{
    std::cout << "Test successful: " << message << "\n";
}

int main(int argc, char* argv[])
{
    GameEngine& game = Global::game;

    game.run(new TestGameState);

    return 0;
}

#include "States/MainMenuState.hpp"

#include "GameEngine.hpp"
#include "Global.hpp"
#include "StateMachine.hpp"

void MainMenuState::handleEvent(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        Global::game.quit();
        break;
    }
}

void MainMenuState::update()
{

}

void MainMenuState::render()
{

}

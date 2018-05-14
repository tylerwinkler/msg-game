#include "StateMachine.hpp"

#include "State.hpp"

StateMachine::StateMachine() : m_pendingState(nullptr)
{
}

void StateMachine::changeState(State* newState)
{
    m_pendingState = newState;
}

void StateMachine::pushState(State* newState)
{
    m_activeState = newState;

    if (!m_activeState->init())
    {
        throw "State init failed";
    }
}

State* StateMachine::getState()
{
    return m_activeState;
}

bool StateMachine::hasPendingStateChange()
{
    return m_pendingState != nullptr;
}

void StateMachine::processPendingStateChange()
{
    m_activeState->cleanup();

    delete m_activeState;

    m_activeState = m_pendingState;

    if (!m_activeState->init())
    {
        throw "State init failed";
    }

    m_pendingState = nullptr;
}

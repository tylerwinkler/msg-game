#ifndef MSG_GAME_STATEMACHINE_HPP
#define MSG_GAME_STATEMACHINE_HPP

class State;

class StateMachine
{
public:
    StateMachine();

public:
    void changeState(State* newState);

    void pushState(State* newState);

    State* getState();

    bool hasPendingStateChange();

    void processPendingStateChange();

private:
    State* m_activeState;

    State* m_pendingState;
}; // StateMachine

#endif // MSG_GAME_STATEMACHINE_HPP

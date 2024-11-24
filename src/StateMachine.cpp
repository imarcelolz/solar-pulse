#include "StateMachine.h"

StateMachine::StateMachine(int initialState, int errorState)
{
    this->initialState = this->state = initialState;
    this->errorState = errorState;
}

int StateMachine::getState()
{
    return this->state;
}

bool StateMachine::hasError()
{
    return this->state == this->errorState;
}

void StateMachine::addEvent(int event, EventHandler handler)
{
    this->eventHandlers[event] = handler;
}

void StateMachine::removeEvent(int event)
{
    this->eventHandlers.erase(event);
}

void StateMachine::loop()
{
    if (this->hasError() || this->eventHandlers.count(this->state) == 0) {
        return;
    }

    try {
        auto handler = this->eventHandlers[this->state];
        this->state = handler();
    } catch(...) {
        this->state = this->errorState;
    }
}

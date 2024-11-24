#pragma once

#include <map>

typedef int (*EventHandler)();

class StateMachine {
    int state = 0;
    int initialState = 0;
    int errorState = 0;

    std::map<int, EventHandler> eventHandlers;

public:
    StateMachine(int initialState, int errorState);

    int getState();
    bool hasError();
    void addEvent(int event, EventHandler handler);
    void begin();
    void loop();
    void removeEvent(int event);
    void reset();
};

# pragma once

enum State {
    STATE_UNDEFINED = 0,
    STATE_BOOTING,
    // STATE_WIFI_CONNECTED,
    // STATE_SERVER_ENABLED,
    // STATE_FATAL_ERROR,
};
// typedef EventHandler

class StateMachine {
    State state = STATE_UNDEFINED;
    // eventHandlers
    public:

    void begin();
    State getState();
    void loop();
};


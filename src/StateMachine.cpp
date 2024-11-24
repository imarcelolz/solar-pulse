#include "StateMachine.h"

void StateMachine::begin() {
    this->state = STATE_BOOTING;
}

State StateMachine::getState() {
    return this->state;
}

void StateMachine::loop() {
//     switch (this->state)
//     {
//         case STATE_BOOTING:
//             onBooting();
//             break
//         case STATE_WIFI_SETUP:
//             onWifiSetup();
//             break;
//         case STATE_WIFI_CONNECTED:
//             onWifiConnected();
//         case 
// ,
// ,
// ,
// STATE_SERVER_ENABLED,
// STATE_FATAL_ERROR,;

//     default:
//         break;
//     }
}



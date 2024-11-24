#include <StateMachine.h>
#include <mainEvents.h>

StateMachine stateMachine(STATE_BOOTING, STATE_FATAL_ERROR);

void setup() {
    stateMachine.addEvent(STATE_BOOTING, onBooting);
    stateMachine.addEvent(STATE_WIFI_SETUP, onWifiSetup);
    stateMachine.addEvent(STATE_WIFI_CONNECTED, onWifiConnected);
    stateMachine.addEvent(STATE_MAIN, onMain);
}

void loop() {
    stateMachine.loop();
}

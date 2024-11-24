
enum State {
    STATE_UNDEFINED = 0,
    STATE_BOOTING,
    STATE_WIFI_SETUP,
    STATE_WIFI_CONNECTED,
    STATE_MAIN,
    STATE_FATAL_ERROR,
};

int onBooting();
int onWifiSetup();
int onWifiConnected();
int onMain();
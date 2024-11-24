#include <mainEvents.h>

#include <HardwareSerial.h>
#include <WiFi.h>
#include <WiFiManager.h>

#include "Display.h"
#include "lib.h"

#define DEVICE_NAME "ESP-Monitor"
#define SCREEN_ADDRESS 0x3C
#define LOOP_DELAY 1000
#define WIFI_CONNECT_TIMEOUT_SECONDS 30
#define WIFI_PORTAL_TIMEOUT_SECONDS 30

int ledPins[4] = { 0, 1, 2, 3 };
Display display(&Wire, SCREEN_ADDRESS, ledPins);
WiFiManager wifiManager;

int onBooting()
{
    Serial.begin();
    Wire.begin(20, 21);
    display.begin();

    display.updateFirstLine("What's up!", true);

    wifiManager.setConfigPortalTimeout(WIFI_CONNECT_TIMEOUT_SECONDS);
    wifiManager.setConnectTimeout(WIFI_PORTAL_TIMEOUT_SECONDS);
    wifiManager.setConfigPortalBlocking(false);

    return (int)STATE_WIFI_SETUP;
}

int onWifiSetup() {
    display.updateFirstLine("I'm trying to connect to wifi", true);

    if (wifiManager.autoConnect(DEVICE_NAME)) {
        return (int)STATE_WIFI_CONNECTED;
    }

    return (int)STATE_WIFI_SETUP;
}

int onWifiConnected()
{
    display.updateFirstLine("Waiting data...");
    display.updateSecondLine(WiFi.localIP().toString(), true);

    return (int)STATE_MAIN;
}

int onMain()
{
    delay(LOOP_DELAY);

    return (int)STATE_MAIN;
}

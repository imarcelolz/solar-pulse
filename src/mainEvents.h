#pragma once

#include <HardwareSerial.h>
#include <WString.h>
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiManager.h>

#ifndef ESPAsyncWebServer
#define ESPAsyncWebServer
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#endif

#include "Display.h"

#define DEVICE_NAME "ESP-Monitor"
#define SCREEN_ADDRESS 0x3C
#define LOOP_DELAY 1000
#define WIFI_CONNECT_TIMEOUT_SECONDS 30
#define WIFI_PORTAL_TIMEOUT_SECONDS 30
#define WIFI_MANAGER_PORT 81

enum State {
  STATE_UNDEFINED = 0,
  STATE_BOOTING,
  STATE_WIFI_SETUP,
  STATE_MAIN,
  STATE_FATAL_ERROR,
};

int onBooting();
int onWifiSetup();
int onMain();

void onApiData(String data);

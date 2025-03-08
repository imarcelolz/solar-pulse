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

#include "lib/Display.h"
#include "lib/StateMachine.h"

#define I2C_SCREEN_ADDRESS 0x3C
#define LED_PIN_0 0
#define LED_PIN_1 1
#define LED_PIN_2 2
#define LED_PIN_3 3
#define LOOP_DELAY 1000
#define WIFI_CONNECTION_TIMEOUT_SECONDS 300
#define WIFI_DEVICE_NAME "monitor-cozinha"
#define WIFI_PORTAL_PORT 81
#define WIFI_PORTAL_TIMEOUT_SECONDS 30
#define WIFI_SSID "MoguekoWireless"
#define WIFI_SSID_PASSWORD "#bratraquiana123#"

enum State {
  STATE_UNDEFINED = 0,
  STATE_BOOTING,
  STATE_WIFI_SETUP,
  STATE_MAIN,
  STATE_FATAL_ERROR,
};

int onBooting();
int onMain();
int onWifiSetup();
void onApiData(String data);

void updateDisplay(String data);
void webserverOnData(AsyncWebServerRequest *request);
void webServerOnNotFound(AsyncWebServerRequest *request);

#include "wifi.h"

void onWifiConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  Serial.println("[+] Connected to the WiFi network");
}

void onWifiDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  Serial.println("[-] Disconnected from the WiFi AP");
//   WiFi.begin(ssid, password);
}

void wifiConnect(String ssid, String password) {
  WiFi.onEvent(onWifiConnected, ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(onWifiDisconnected, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  WiFi.begin(ssid, password);
}
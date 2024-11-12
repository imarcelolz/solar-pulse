#include <WiFi.h>
#include <string>

void onWifiConnected(WiFiEvent_t event, WiFiEventInfo_t info);
void onWifiDisconnected(WiFiEvent_t event, WiFiEventInfo_t info);
void wifiConnect(String ssid, String password);
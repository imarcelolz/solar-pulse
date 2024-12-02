
#include <mainEvents.h>

int ledPins[4] = {0, 1, 2, 3};

Display display(&Wire, SCREEN_ADDRESS, ledPins);
WiFiManager wifiManager;

AsyncWebServer webServer(80);

void webserverOnData(AsyncWebServerRequest *request);
void webserverOnPostData(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
void webServerOnNotFound(AsyncWebServerRequest *request);

void updateDisplay(String data);

int onBooting() {
  Serial.begin();
  Wire.begin(20, 21);

  display.begin();
  display.updateFirstLine("Booting", true);

  wifiManager.setHttpPort(WIFI_MANAGER_PORT);
  wifiManager.setConfigPortalTimeout(WIFI_CONNECT_TIMEOUT_SECONDS);
  wifiManager.setConnectTimeout(WIFI_PORTAL_TIMEOUT_SECONDS);
  wifiManager.setConfigPortalBlocking(false);

  webServer.on("/api", HTTP_GET, webserverOnData);
  webServer.on("/api", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, webserverOnPostData);

  webServer.onNotFound(webServerOnNotFound);

  return (int)STATE_WIFI_SETUP;
}

int onMain() {
  delay(200);

  auto nextState = WiFi.isConnected() ? STATE_MAIN : STATE_WIFI_SETUP;

  return (int)nextState;
}

void webserverOnData(AsyncWebServerRequest *request) {
  Serial.println("webserverOnData");

  request->send(200, "text/plain", "Ok");
  updateDisplay(request->arg("data"));
}

void webserverOnPostData(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  if (total != display.totalSize()) {
    request->send(500, "text/plain", "The total does not match the display size");
    return;
  }

  display.updateBitmap(data, true);

  request->send(200, "text/plain", "Ok");
}

void webServerOnNotFound(AsyncWebServerRequest *request) {
  Serial.println("webServerOnNotFound");

  request->send(404, "text/plain", "Not found");
}

void updateDisplay(String data) {
  Serial.println(data);

  String buffer[2];
  short index = 0;

  for (int i = 5; i < data.length(); i++) {
    if (data[i] == ';') {
      index++;
      continue;
    }

    buffer[index] += data[i];
  }

  display.updateLeds(
      data[0] == '1',
      data[1] == '1',
      data[2] == '1',
      data[3] == '1');

  display.updateFirstLine(buffer[0]);
  display.updateSecondLine(buffer[1], true);
}

int onWifiSetup() {
  auto wifiConnected = []() {
    webServer.begin();

    display.updateFirstLine("Connected!");
    display.updateSecondLine(WiFi.localIP().toString(), true);

    return (int)STATE_MAIN;
  };

  webServer.end();
  display.updateFirstLine("Connecting", true);

  if (wifiManager.autoConnect(DEVICE_NAME)) {
    return wifiConnected();
  }

  display.updateFirstLine("Setup me in");
  display.updateSecondLine(DEVICE_NAME, true);

  while (!WiFi.isConnected()) {
    wifiManager.process();
  }

  return wifiConnected();
}

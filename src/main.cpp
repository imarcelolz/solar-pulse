#include <main.h>

int ledPins[4] = {LED_PIN_0, LED_PIN_1, LED_PIN_2, LED_PIN_3};

Display display(&Wire, I2C_SCREEN_ADDRESS, ledPins);
WiFiManager wifiManager;
AsyncWebServer webServer(80);

StateMachine stateMachine(STATE_BOOTING, STATE_FATAL_ERROR);

void setup() {
  delay(500);

  stateMachine.addEvent(STATE_BOOTING, onBooting);
  stateMachine.addEvent(STATE_WIFI_SETUP, onWifiSetup);
  stateMachine.addEvent(STATE_MAIN, onMain);
}

void loop() {
  stateMachine.loop();
}

int onBooting() {
  delay(500);

  Serial.begin();
  Wire.begin(20, 21);

  display.begin();
  display.setFontSize(SMALL);
  display.updateFirstLine("Booting", true);

  wifiManager.setConfigPortalBlocking(false);
  wifiManager.setConfigPortalTimeout(WIFI_CONNECTION_TIMEOUT_SECONDS);
  wifiManager.setConnectTimeout(WIFI_PORTAL_TIMEOUT_SECONDS);
  wifiManager.setHttpPort(WIFI_PORTAL_PORT);
  wifiManager.setWiFiAPHidden(false);

  webServer.on("/api", HTTP_GET, webserverOnData);
  webServer.onNotFound(webServerOnNotFound);

  return (int)STATE_WIFI_SETUP;
}

int onMain() {
  delay(200);

  auto nextState = WiFi.isConnected() ? STATE_MAIN : STATE_WIFI_SETUP;

  return (int)nextState;
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

  if (wifiManager.autoConnect(WIFI_DEVICE_NAME)) {
    return wifiConnected();
  }

  display.setFontSize(SMALL);
  display.updateFirstLine("Connect to wifi");
  display.updateSecondLine(WIFI_DEVICE_NAME, true);

  while (!WiFi.isConnected()) {
    wifiManager.process();
    delay(10);
  }

  return wifiConnected();
}

void webserverOnData(AsyncWebServerRequest *request) {
  Serial.println("webserverOnData");

  request->send(200, "text/plain", "Ok");
  updateDisplay(request->arg("data"));
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

  display.setFontSize(LARGE);
  display.updateFirstLine(buffer[0]);
  display.updateSecondLine(buffer[1], true);
}

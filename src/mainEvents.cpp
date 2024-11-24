#include <mainEvents.h>

int ledPins[4] = { 0, 1, 2, 3 };

Display display(&Wire, SCREEN_ADDRESS, ledPins);
WiFiManager wifiManager;

WebServer* webServer = NULL;

void webserverOnData();
void webServerOnNotFound();
void updateDisplay(String data);

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


WebServer* createWebserver() {
    auto newServer = new WebServer(80);

    newServer->on("/api", webserverOnData);
    newServer->onNotFound(webServerOnNotFound);

    newServer->begin();

    return newServer;
}


int onMain()
{
    if(webServer == NULL) {
        webServer = createWebserver();
    }

    webServer->handleClient();

    return (int)STATE_MAIN;
}


void webserverOnData() {
    Serial.println("webserverOnData");
    updateDisplay(webServer->arg("data"));


    webServer->send(200, "text/plain", "Ok");
}

void webServerOnNotFound() {
    Serial.println("webServerOnNotFound");
    webServer->send(404, "text/plain", "Not found");
}

void updateDisplay(String data)
{
    Serial.println(data);

    String buffer[2];
    short index = 0;

    for(int i = 5 ; i < data.length(); i++) {
        if(data[i] == ';') {
            index++;
            continue;
        }

        buffer[index] += data[i];
    }

    display.updateLeds(
        data[0] == '1',
        data[1] == '1',
        data[2] == '1',
        data[3] == '1' 
    );

    display.updateFirstLine(buffer[0]);
    display.updateSecondLine(buffer[1], true);

}

int onWifiSetup()
{
    auto wifiConnected = []() {
        String uri = "http://" + WiFi.localIP().toString() + "/api";
        display.updateFirstLine("Connected!!");
        display.updateSecondLine(uri, true);

        return (int)STATE_MAIN;
    };

    display.updateFirstLine("I'm trying to connect to wifi", true);

    if (wifiManager.autoConnect(DEVICE_NAME)) {
        return wifiConnected();
    }

    display.updateFirstLine("Setup me in via wifi");
    display.updateSecondLine(DEVICE_NAME, true);

    while (!WiFi.isConnected()) {
        wifiManager.process();
    }

    return wifiConnected();
}


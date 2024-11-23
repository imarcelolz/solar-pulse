#include <BluetoothSerial.h>
#include <HardwareSerial.h>

#include "Display.h"
#include "lib.h"

#define DEVICE_NAME "ESP-Monitor"
#define SCREEN_ADDRESS 0x3C
#define LOOP_DELAY 1000
#define SERIAL_BAUD 9600

void dataDebug(Data* data);
void readData(Data* data);
void setPaitingMessage();

int ledPins[4] = { 0, 1, 2, 3 };
Display display(&Wire, SCREEN_ADDRESS, ledPins);
Data data = { "", "", { false, false, false, false } };

void setup()
{
    Serial.begin();
    Wire.begin(20, 21);

    display.begin();

    // serialBt.begin(DEVICE_NAME);
    setPaitingMessage();
}

void loop()
{
    // if (serialBt.available()) {
    //     Serial.println("Data available");
    //     readData(&data);
    //     display.update(&data);
    //     dataDebug(&data);
    // }

    // if (!serialBt.connected()) {
    //     setPaitingMessage();
    // }

    delay(LOOP_DELAY);
}

void readData(Data* data)
{
    // String ledBuffer = serialBt.readStringUntil(';');
    // String firstLine = serialBt.readStringUntil(';');
    // String secondLine = serialBt.readStringUntil('\n');

    // data->firstLine = firstLine;
    // data->secondLine = secondLine.substring(0, secondLine.length() - 1);
    // for (int i = 0; i < LED_COUNT; i++) {
    //     data->leds[i] = ledBuffer[i] == '1';
    // }
}

void setPaitingMessage()
{
    data.firstLine = "BT pair with";
    data.secondLine = DEVICE_NAME;

    display.update(&data);
}

void dataDebug(Data* data)
{
    Serial.println(data->firstLine);
    Serial.println(data->secondLine);
    for (int i = 0; i < 4; i++) {
        Serial.println(data->leds[i]);
    }
}

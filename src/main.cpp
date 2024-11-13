#include <LiquidCrystal_I2C.h>
#include <string>
#include <HardwareSerial.h>
#include "BluetoothSerial.h"

const int SERIAL_BAUD = 9600;
const char* DEVICE_NAME = "ESP-Monitor";
const int LDC_WITDH = 16;
const int LDC_HEIGHT = 2;

struct Data {
  String firstLine;
  String secondLine;
};

void connectBT();
Data* readData();
void update(Data* data);

LiquidCrystal_I2C lcd(0x26, LDC_WITDH, LDC_HEIGHT);
BluetoothSerial serialBt;

Data data = {
  "",
  ""
};

void setup() {
  Serial.begin(SERIAL_BAUD);

  lcd.init();
  lcd.backlight();

  connectBT();
}

void loop() {
  delay(5000);
  return;

  if (!serialBt.available()) {
    delay(5000);
    return;
  }

  update(readData());
}

void connectBT() {
  Serial.println("Connecting to Bluetooth");

  serialBt.begin(DEVICE_NAME);
  data.firstLine = "Bluetooth waiting for pairing";
  data.secondLine = DEVICE_NAME;
  update(&data);
}

Data* readData() {
  Serial.println("Reading data");

  String* buffer = &data.firstLine;
  buffer->clear();

  while (serialBt.available()) {
    char read = serialBt.read();
    if (read == '\n') {
      break;
    }

    if (read == ';') {
      buffer = &data.secondLine;
      buffer->clear();
      continue;
    }

    buffer += read;
  }

  return &data;
}

void update(Data* data) {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(data->firstLine.c_str());
  lcd.setCursor(0, 1);
  lcd.print(data->secondLine.c_str());

  // TODO: Enable/disable pins
}

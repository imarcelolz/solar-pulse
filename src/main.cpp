#include <LiquidCrystal_I2C.h>
#include <string>
#include <HardwareSerial.h>
#include "BluetoothSerial.h"

const String DEVICE_NAME = "ESP-Monitor";
const int BRIGHTNESS = 2;
const int LDC_HEIGHT = 2;
const int LDC_WITDH = 16;
const int LOOP_DELAY = 500;
const int SERIAL_BAUD = 9600;

struct Data {
  String firstLine;
  String secondLine;
};

void connectBT();
void setPaitingMessage();
Data* readData();
void update(Data* data);

LiquidCrystal_I2C lcd(0x27, LDC_WITDH, LDC_HEIGHT);
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
  // lcd.clear();

  // lcd.setCursor(0, 0);
  // lcd.print("Abacateiro");
  // lcd.setCursor(0, 1);
  // lcd.print("Juvelino");
}

void loop() {

  // Serial.print(".");
  // Serial.print(data.firstLine + " ");
  // Serial.println(data.secondLine);

  // if (serialBt.available()) {
  //   update(readData());
  // }

  // if (!serialBt.hasClient()) {
  //   connectBT();
  // }

  delay(LOOP_DELAY);
}

void setPaitingMessage() {
  data.firstLine = "BT pair with";
  data.secondLine = DEVICE_NAME;

  update(&data);
}

void connectBT() {
  Serial.println("Connecting to Bluetooth");

  serialBt.begin(DEVICE_NAME);
  setPaitingMessage();
}

Data* readData() {
  Serial.println("Reading data");

  data.firstLine = serialBt.readStringUntil(';');
  data.secondLine = serialBt.readStringUntil('\n');

  return &data;
}

void update(Data* data) {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(data->firstLine);
  lcd.setCursor(0, 1);
  lcd.print(data->secondLine);

  // TODO: Enable/disable pins
}

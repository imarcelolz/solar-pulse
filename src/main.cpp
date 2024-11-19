#include <LiquidCrystal_I2C.h>
#include <string>
#include <HardwareSerial.h>
#include "BluetoothSerial.h"

const String DEVICE_NAME = "ESP-Monitor";
const int BRIGHTNESS = 2;
// const int LCD_ADDR = 0x27;
const int LDC_HEIGHT = 2;
const int LDC_WITDH = 16;
const int LOOP_DELAY = 1000;
const int SERIAL_BAUD = 9600;
const int LED_COUNT = 4;
const int LED_PINS[4] = {13, 12, 14, 27};

struct Data {
  String firstLine;
  String secondLine;
  bool leds[4];
};

void connectBT();
void setPaitingMessage();
void updateDisplay(Data* data);
void readData(Data* data);
void debugData(Data* data);
void scanI2C();

LiquidCrystal_I2C lcd(0x27, LDC_WITDH, LDC_HEIGHT);
BluetoothSerial serialBt;

Data data = {
  "",
  "",
  {false, false, false, false}
};


void setup() {
  Serial.begin(SERIAL_BAUD);

  lcd.init();
  lcd.backlight();

  Serial.println("Connecting to Bluetooth");
  serialBt.begin(DEVICE_NAME);
  setPaitingMessage();

  for(int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], HIGH);
  }
}

void loop() {
  // scanI2C();

  if(serialBt.available()) {
    Serial.println("Data available");
    readData(&data);
    updateDisplay(&data);
    debugData(&data);
  }

  if(!serialBt.connected()) {
    setPaitingMessage();
  }

  delay(LOOP_DELAY);
}

void readData(Data* data) {
  String ledBuffer = serialBt.readStringUntil(';');
  String firstLine = serialBt.readStringUntil(';');
  String secondLine = serialBt.readStringUntil('\n');

  data->firstLine = firstLine;
  data->secondLine = secondLine.substring(0, secondLine.length() - 1);
  for(int i = 0; i < LED_COUNT; i++) {
    data->leds[i] = ledBuffer[i] == '1';
  }
}

void updateDisplay(Data* data) {
  lcd.clear();

  lcd.setCursor(0, 0);
  debugData(data);
  lcd.print(data->firstLine);
  lcd.setCursor(0, 1);
  lcd.print(data->secondLine);

  for(int i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], data->leds[i] ? HIGH : LOW);
  }
}

void debugData(Data* data) {
  Serial.println(data->firstLine);
  Serial.println(data->secondLine);
  for(int i = 0; i < LED_COUNT; i++) {
    Serial.println(data->leds[i]);
  }
}

void setPaitingMessage() {
  data.firstLine = "BT pair with";
  data.secondLine = DEVICE_NAME;

  updateDisplay(&data);
}

void scanI2C() {
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
      nDevices++;
    }
    else if (error==4) {
      Serial.print("Unknow error at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("done\n");
  }
}
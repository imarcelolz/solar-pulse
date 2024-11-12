#include "wifi.h"
// #include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int SERIAL_BAUD = 9600;
const String ssid = "";
const String password = "";

struct Data {
  String firstLine;
  String secondLine;
};

LiquidCrystal_I2C lcd(0x27, 16, 2);
void print(String firstLine, String secondLine);
Data fetchData();

void setup() {
  Serial.begin(SERIAL_BAUD);
  lcd.init();
  lcd.backlight();

  print("Wifi", "Connecting...");
  wifiConnect(ssid, password);
}

void loop() {
  Data data = fetchData();

  print(data.firstLine, data.secondLine);

  delay(2250);
}

void print(String firstLine, String secondLine = "") {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(firstLine);
  lcd.setCursor(0, 1);
  lcd.print(secondLine);
}


Data fetchData() {
  return {
    "Hello, World!",
    "This is a test"
  };
}


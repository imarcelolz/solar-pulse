#pragma once

#include <Adafruit_SSD1306.h>
#include <WString.h>
#include <Wire.h>

#define DISPLAY_HEIGHT 32
#define DISPLAY_WITDH 128
#define LED_COUNT 4
#define LINE_HEIGHT 16
#define OLED_RESET -1
#define TEXT_SIZE 1

struct Data {
  String firstLine;
  String secondLine;
  bool leds[4];
};

class Display {
  Adafruit_SSD1306* display;
  int address;
  int ledPins[LED_COUNT];
  Data data = {"", "", {false, false, false, false}};

 public:
  Display(TwoWire* wire, int address, int ledPins[LED_COUNT]);

  void begin();
  void updateFirstLine(String line, bool refresh = false);
  void updateSecondLine(String line, bool refresh = false);
  void updateLeds(bool led1, bool led2, bool led3, bool led4, bool refresh = false);
  void update(Data data, bool refresh = false);
  void refresh();
};

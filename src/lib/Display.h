#pragma once

#include <Adafruit_SSD1306.h>
#include <WString.h>
#include <Wire.h>

#define DISPLAY_HEIGHT 32
#define DISPLAY_WITDH 128
#define DISPLAY_LED_COUNT 4
#define DISPLAY_LINE_HEIGHT 16
#define DISPLAY_OLED_RESET -1
#define DISPLAY_TEXT_SIZE 2

struct Data {
  String firstLine;
  String secondLine;
  bool leds[DISPLAY_LED_COUNT];
};

class Display {
  Adafruit_SSD1306* display;
  int address;
  int ledPins[DISPLAY_LED_COUNT];
  Data data = {"", "", {false, false, false, false}};

 public:
  Display(TwoWire* wire, int address, int ledPins[DISPLAY_LED_COUNT]);

  void begin();
  void updateFirstLine(String line, bool refresh = false);
  void updateSecondLine(String line, bool refresh = false);
  void updateLeds(bool led1, bool led2, bool led3, bool led4, bool refresh = false);
  void update(Data data, bool refresh = false);
  size_t totalSize();

  void refresh();
};

#pragma once

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "lib.h"

#define DISPLAY_HEIGHT 32
#define DISPLAY_WITDH 128
#define LED_COUNT 4
#define LINE_HEIGHT 16
#define OLED_RESET -1
#define TEXT_SIZE 1

class Display {
    Adafruit_SSD1306 *display;
    int address;
    int ledPins[LED_COUNT];

    public:
    Display(TwoWire* wire, int address, int ledPins[LED_COUNT]);

    void begin();
    void update(Data* data);
};

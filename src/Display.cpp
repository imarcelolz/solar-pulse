#include "Display.h"

Display::Display(TwoWire* wire, int address, int ledPins[LED_COUNT])
{
    this->address = address;
    this->display = new Adafruit_SSD1306(DISPLAY_WITDH, DISPLAY_HEIGHT, wire);

    for(int i = 0 ; i < LED_COUNT; i++) {
        this->ledPins[i] = ledPins[i];
    }
}

void Display::begin()
{
    this->display->begin(SSD1306_SWITCHCAPVCC, this->address);
    this->display->setTextSize(TEXT_SIZE);
    this->display->setTextColor(SSD1306_WHITE);

    for (int i = 0; i < LED_COUNT; i++) {
        pinMode(this->ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }
}

void Display::update(Data* data)
{
    this->display->clearDisplay();

    this->display->setCursor(0, 0);
    this->display->println(data->firstLine);

    this->display->setCursor(0, LINE_HEIGHT);
    this->display->println(data->secondLine);

    display->display();

    for (int i = 0; i < LED_COUNT; i++) {
        digitalWrite(this->ledPins[i], data->leds[i] ? HIGH : LOW);
    }
}
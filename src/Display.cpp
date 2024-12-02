#include "Display.h"

Display::Display(TwoWire* wire, int address, int ledPins[LED_COUNT]) {
  this->address = address;
  this->display = new Adafruit_SSD1306(DISPLAY_WITDH, DISPLAY_HEIGHT, wire);

  for (int i = 0; i < LED_COUNT; i++) {
    this->ledPins[i] = ledPins[i];
  }
}

void Display::begin() {
  this->display->begin(SSD1306_SWITCHCAPVCC, this->address);
  this->display->setTextSize(TEXT_SIZE);
  this->display->setTextColor(SSD1306_WHITE);

  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(this->ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void Display::refresh() {
  this->display->clearDisplay();

  this->display->setCursor(0, 0);
  this->display->println(this->data.firstLine);

  this->display->setCursor(0, LINE_HEIGHT);
  this->display->println(this->data.secondLine);

  display->display();

  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(this->ledPins[i], this->data.leds[i] ? HIGH : LOW);
  }
}

void Display::updateFirstLine(String line, bool refresh) {
  this->data.firstLine = line;

  if (refresh) {
    this->refresh();
  }
}

void Display::updateSecondLine(String line, bool refresh) {
  this->data.secondLine = line;

  if (refresh) {
    this->refresh();
  }
}

void Display::updateLeds(bool led1, bool led2, bool led3, bool led4, bool refresh) {
  this->data.leds[0] = led1;
  this->data.leds[1] = led2;
  this->data.leds[3] = led3;
  this->data.leds[3] = led4;

  if (refresh) {
    this->refresh();
  }
}

void Display::update(Data data, bool refresh) {
  this->data.firstLine = data.firstLine;
  this->data.secondLine = data.secondLine;
  this->updateLeds(data.leds[0], data.leds[1], data.leds[2], data.leds[3], refresh);
}

void Display::updateBitmap(uint8_t* bitmap, bool refresh) {
  this->display->clearDisplay();
  this->display->drawBitmap(
      0, 0, bitmap, DISPLAY_WITDH, DISPLAY_HEIGHT, 1);
  display->display();
}

size_t Display::totalSize() {
  return DISPLAY_HEIGHT * DISPLAY_WITDH;
}
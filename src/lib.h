#pragma once

#include <Wire.h>
#include <HardwareSerial.h>
#include <string>

void i2cScaner();

struct Data {
    String firstLine;
    String secondLine;
    bool leds[4];
};

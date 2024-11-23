#include "lib.h"

void i2cScaner()
{
    short error;
    int devices = 0;

    Serial.println("Scanning...");

    for (short address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error != 0) {
            continue;
        }

        Serial.print("I2C device found at address 0x");

        if (address < 16)
            Serial.print("0");

        Serial.print(address, HEX);
        Serial.println("  !");
    }
}

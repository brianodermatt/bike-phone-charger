/**
 * This module provides all functions for using the I2C bus (read, write) of the arduino
 */
#include<Wire.h>

void i2cSetup () {
  Wire.begin();
}

void i2cDeviceScan () {
  byte nDevices = 0, success;

  for (byte address = 1; address < 127; address++) {
    // Use return value of Write.endTransmisstion to see if a device acknowledges at address.
    Wire.beginTransmission(address);
    success = Wire.endTransmission();
    
    if (success == 0) {
      Serial.print("I2C device found at addresss 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    } else if (success == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0) {
    Serial.println("No I2C devices found in scan");
  }
}

/**
 * This module provides all functions for using the I2C bus (read, write) of the arduino
 */
#include "main.h"

#include<Wire.h>

void i2cSetup (void) {
  Wire.begin();
}

void i2cDeviceScan (void) {
  byte nDevices = 0, success;

  for (byte address = 1; address < 127; address++) {
    // Use return value of Write.endTransmisstion to see if a device acknowledges at address.
    Wire.beginTransmission(address);
    success = Wire.endTransmission();
    if (success == 0) {
      echo("I2C device found at addresss 0x");
      if (address < 16) echo("0");
      echoln(address, HEX);
      nDevices++;
    } else if (success == 4) {
      echo("Unknown error at address 0x");
      if (address < 16) echo("0");
      echoln(address, HEX);
    }
  }

  if (nDevices == 0) {
    echoln("No I2C devices found in scan");
  }
}

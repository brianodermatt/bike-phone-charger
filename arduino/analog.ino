/**
 * This module provides all functions for analog (read, write)
 */
#include "main.h"

#define INPUT_RANGE 1024.0

float analogReadWithinRange(byte pin, float offset, float range) {
  int sensorValue = analogRead(pin);
  float sensorNormalised = sensorValue * range / INPUT_RANGE;
  echo("measure "); echoln(sensorValue);
  return sensorNormalised;
}

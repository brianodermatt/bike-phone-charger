/**
 * Main module. Setup and loop function
 */
#include "main.h"

int sensorPin = A0;
int integrationStep = 1000; // time in ms

// setup: is run once, at the beginning
void setup() {
  logSetup();
  i2cSetup();
  i2cDeviceScan();
  displaySetup();
  resetIntegration();
}

// main loop
void loop() {
  integrateStep();
  delay(integrationStep);
}

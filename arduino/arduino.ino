/**
 * Main module. Setup and loop function
 */
#include "main.h"

int integrationStep = 1000; // time in ms

// setup: is run once, at the beginning
void setup() {
  logSetup();
  i2cSetup();
  i2cDeviceScan();
  displaySetup();
  integratorSetup();
}

// main loop
void loop() {
  integrateStep();
  delay(integrationStep);
  if (digitalRead(RESET_PIN) == HIGH) {
    // reset
    resetIntegration();
  }
}

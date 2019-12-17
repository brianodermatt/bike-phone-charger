/**
 * Main module. Setup and loop function
 */
#include "main.h"
#include "display.h"
#define RESET_DURATION  3   // seconds to hold the reset button for actually resetting

int integrationStep = 1000; // time in ms

// setup: is run once, at the beginning
void setup() {
  logSetup();
  i2cSetup();
  i2cDeviceScan();
  delay(500);
  displaySetup();
  integratorSetup();
  pinMode(RESET_PIN, INPUT);
}

// main loop
void loop() {
  static int reset_time = 0;
  integrateStep();
  //if (digitalRead(RESET_PIN) == HIGH) {
  if (analogRead(RESET_PIN) > 500) {
    displayResetting = true;
    if (reset_time > 2) {
      resetIntegration();
      reset_time = 0;
    }
    else reset_time++;
  } else displayResetting = false;
  delay(integrationStep);
}

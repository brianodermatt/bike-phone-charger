/**
 * Main module. Setup and loop function
 */
int sensorPin = A0;
int integrationStep = 1000; // time in ms

// setup: is run once, at the beginning
void setup() {
  Serial.begin(9600);
  while (!Serial);  // wait for serial monitor
  i2cSetup();
  i2cDeviceScan();
  resetIntegration();
}

// main loop
void loop() {
  integrateStep();
  delay(integrationStep);
}

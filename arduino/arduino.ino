int sensorPin = A0;
int integrationStep = 1000; // time in ms

// setup: is run once, at the beginning
void setup() {
  Serial.begin(9600);
  resetIntegration();
}

// main loop
void loop() {
  integrateStep();
  delay(integrationStep);
}

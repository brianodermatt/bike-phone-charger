/**
 * Integration over lifetime of: power
 * Uses EEPROM addresses 0,1,2,3
 */
#define POWER_ADDRESS 0
#define POWER_PIN A0

void resetIntegration(void) {
  eepromWriteFloat(POWER_ADDRESS, 0.0);
}

void integrateStep(void) {
  float currentPowerIntegral = eepromReadFloat(POWER_ADDRESS);
  float measure = analogReadWithinRange(POWER_PIN, 0.0, 5.0);
  float accumulate = currentPowerIntegral + measure * (integrationStep/1000.0);
  eepromWriteFloat(POWER_ADDRESS, accumulate);
  Serial.println(accumulate);
}

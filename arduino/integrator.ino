/**
 * Integration over lifetime of: power
 * Uses EEPROM addresses 0,1,2,3
 */
#define POWER_ADDRESS 0 // addr 0 - 3
#define POWER_PIN A0
#define POWER_PRECISION 16  // 2^4 = 16 possible decimal states of the power. i.e. the value saved is 16 times bigger than the measure

void resetIntegration(void) {
  eepromWriteLong(POWER_ADDRESS, 0.0);
}

/*
 * overflow duration T: longMax = 2^32, log_2_POWER_PRECISION bits are used for decimal points
 * T = dt * 2^(32-log_2_POWER_PRECISION) / V_typ
 * for power: V_typ = R*P_typ/5[V] = 1[Ohm]*1[W]/5[V], dt = 1s --> T=75'000h (active)
 */

/* execute one summation step */
void integrateStep(void) {
  // read from EEPROM
  long currentPowerIntegral = eepromReadLong(POWER_ADDRESS);

  // read sensor
  float powerMeasure = POWER_PRECISION * analogReadWithinRange(POWER_PIN, 0.0, 5.0);

  // accumulate
  long powerAccumulate = currentPowerIntegral + (int) (powerMeasure * (integrationStep/1000.0));
  
  // write to EEPROM
  eepromWriteLong(POWER_ADDRESS, powerAccumulate);
  
  Serial.println(powerAccumulate / (float) POWER_PRECISION);
}

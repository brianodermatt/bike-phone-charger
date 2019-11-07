/**
 * Integration over lifetime of: power
 * Uses EEPROM addresses 0,1,2,3
 */
#include "main.h"

#define POWER_ADDRESS 0 // addr 0 - 3
#define POWER_PIN A0
#define POWER_PRECISION 16  // 2^4 = 16 possible decimal states of the power. i.e. the value saved is 16 times bigger than the measure
#define POWER_TEST_R 1  // test resistance of xx Ohm
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
  // read between 0 and 5 V, P = Vdd * Ut / Rt where Ut is the measure and Vdd is the USB+ (5V)
  float powerMeasure = POWER_PRECISION * analogReadWithinRange(POWER_PIN, 0.0, 5.0) * 5 / POWER_TEST_R; 

  // accumulate
  long powerAccumulate = currentPowerIntegral + (int) (powerMeasure * (integrationStep/1000.0));
  
  // write to EEPROM
  if (powerAccumulate > currentPowerIntegral) {
    eepromWriteLong(POWER_ADDRESS, powerAccumulate);
    echo(powerAccumulate / (float) POWER_PRECISION); echoln(" J used so far");
  } else {  // not harvesting
    echoln("Not harvesting");
  }
}

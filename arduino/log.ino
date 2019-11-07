/**
 * Logging using the serial channel. Enable/disable by setting the verbose in log.h 
 * Use echo or echoln for logging
 */
#include "main.h"

void logSetup (void) {
  if (VERBOSE) {
    Serial.begin(9600);
    while (!Serial);  // wait for serial monitor
  }
}

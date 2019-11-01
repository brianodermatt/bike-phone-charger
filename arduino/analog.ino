#define INPUT_RANGE 1024.0

float analogReadWithinRange(byte pin, float offset, float range) {
  int sensorValue = analogRead(pin);
  float sensorNormalised = sensorValue * range / INPUT_RANGE;
  return sensorNormalised;
}

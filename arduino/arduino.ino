int sensorPin = A0;

// setup: is run once, at the beginning
void setup() {
  Serial.begin(9600);
}

// main loop
void loop() {
  // read the value from the sensor:
  int sensorValue = analogRead(sensorPin);
  double sensorVolts = sensorValue * 5.0 / 1024.0;
  Serial.println(sensorVolts);
  delay(500);
}

float vin, current, mA, capacity = 0;
const float batteryVoltage = 8.1;
const float r1 = 4700.0;             // Resistance of the first resistor in ohms
const float r2 = 4700.0;             // Resistance of the second resistor in ohms
const float ratio = (r1 + r2) / r2;  // Voltage divider ratio
const float load = 9.2;              // Voltage divider ratio

unsigned long previousMillis = 0;
unsigned long millisPassed = 0;

void setup(void) {
  Serial.begin(115200);
}

void loop() {
  vin = analogRead(A0) * (5.0 / 1024.0) * ratio;  // Calculate the actual battery voltage
  current = vin / load;                           // Calculate the current flowing through the circuit
  millisPassed = millis() - previousMillis;

  mA = current * 1000.0;                        // Convert current to milliamperes
  capacity += (mA * millisPassed / 3600000.0);  // Update capacity in mAh

  previousMillis = millis();

  Serial.print(vin);   Serial.print(" ");
  Serial.print(current * 1000.0);Serial.print(" ");
  Serial.println(capacity);

  delay(13000);  // Wait for 10 seconds before the next measurement
}

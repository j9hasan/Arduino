// Hardware Serial 2 pins
#define RXD2 16
#define TXD2 17

void setup() {

  Serial.begin(38400);
  Serial.println("Enter AT Commands:");
  // BTSerial.begin(38400);  // HC-05 default speed in AT command mode
  // Serial2.begin(38400, SERIAL_8N1, RXD2, TXD2);
  Serial2.begin(9600);
}

void loop() {

  //The code below allows for commands and messages to be sent from COMPUTER (serial monitor) -> HC-05
  if (Serial.available())          // Keep reading from Arduino Serial Monitor
    Serial2.write(Serial.read());  // and send to HC-05

  //The code below allows for commands and messages to be sent from HC-05 -> COMPUTER (serial monitor)
  if (Serial2.available())         // Keep reading from HC-05 and send to Arduino
    Serial.write(Serial2.read());  // Serial Monitor
}
#include <HardwareSerial.h>

HardwareSerial SerialBT(2);

void setup() {
  Serial.begin(115200);
  SerialBT.begin(9600, SERIAL_8N1, 19, 21);
}
int wait = 2000;
int lastmillis = 0;

void loop() {

  // if (SerialBT.available()) {
  //   SerialBT.write(Serial.read());
  // }

  if ((millis() - lastmillis) > wait) {
    char *incomingByte = "test\n";
    SerialBT.write(incomingByte);
    Serial.println("Data sent");
    lastmillis = millis();
  }

  if (SerialBT.available()) {
    Serial.print(SerialBT.read());
  }
}

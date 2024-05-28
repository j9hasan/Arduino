//Send Hello

#include <SPI.h>
#include <LoRa.h>

int counter = 0;
#define TXEN 27
#define RXEN 22
void setup()
{

  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("LoRa Sender");
  // pinMode(TXEN, OUTPUT);
  // pinMode(RXEN, OUTPUT);
  // digitalWrite(TXEN, HIGH); // tx
  // digitalWrite(RXEN, LOW);  // rx
  // LoRa.setPins(15, -1, -1);
  if (!LoRa.begin(915E6))
  {
    Serial.println("Starting LoRa failed!");

    while (1)
      ;
  }
    LoRa.setTxPower(30);
}

void loop()
{
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("Hello");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(1000);
}
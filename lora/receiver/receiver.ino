//RECEIVER
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <LoRa.h>

#define TXEN 32
#define RXEN 33
#define STATUS_LED 5

#define RST -1
#define CE 21
#define DC 4
#define DIN 16
#define CLK 17
#define LCD_BL 2

bool STATUS_LED_STATE = 0;

Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, CE, RST);

void DispSetup() {
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH);
  Serial.begin(115200);
  Serial.println("PCD test");
  display.begin();

  display.setContrast(60);

  display.clearDisplay();
  display.setRotation(0);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Init Display");
  display.setTextSize(1);
  display.println("Done..");
  display.display();
  delay(1000);
}

void setup() {
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, LOW);
  // pinMode(TXEN, OUTPUT);
  // pinMode(RXEN, OUTPUT);
  // digitalWrite(TXEN, LOW);  // tx
  // digitalWrite(RXEN, HIGH); // rx

  //setup display
  DispSetup();

  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Starting LoRa failed!");
    display.display();
    delay(1000);
    while (1)
      ;
  }
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Receiver Mode");
  display.display();
}

String data;

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
  
    // clear the data string
    data = "";

    // read packet
    while (LoRa.available()) {
      char receivedChar = (char)LoRa.read();
      data += receivedChar;
    }
    Serial.printf("Received packet %s with RSSI %d\n",data,LoRa.packetRssi());

    display.clearDisplay();
    display.setCursor(12, 0);
    display.printf("RF Receiver");
    display.setCursor(0, 15);
    display.printf("Data:%s", data);
    display.setCursor(0, 25);
    display.printf("RSSI:%d", LoRa.packetRssi());

    display.display();

    STATUS_LED_STATE = !STATUS_LED_STATE;
    digitalWrite(STATUS_LED, STATUS_LED_STATE);
  }
}
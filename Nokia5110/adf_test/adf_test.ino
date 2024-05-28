

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define RST -1
#define CE 21
#define DC 4
#define DIN 16
#define CLK 17
#define LCD_BL 2

Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, CE, RST);



void setup() {

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
  display.println("Init system");
  display.setTextSize(1);
  display.println("Done..");
  display.display();
  delay(2000);
}
int i = 0;

void loop() {
  display.clearDisplay();
  // display.setRotation(0);
  // display.setTextSize(1);
  // display.setTextColor(BLACK);
  display.setCursor(12, 0);
  display.printf("RF Receiver");
  display.setCursor(0, 17);
  display.print("Data     RSSI");
  display.setCursor(0, 26);
  display.printf("Hello");
  display.setCursor(54, 26);
  display.printf("%d\n", i);

  display.display();
  delay(2000);
  i++;
}

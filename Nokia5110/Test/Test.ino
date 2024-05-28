#include "Nokia_5110.h"

#define RST -1
#define CE 21
#define DC 4
#define DIN 16
#define CLK 17

Nokia_5110 lcd = Nokia_5110(RST, CE, DC, DIN, CLK);


void setup() {
    /**
     * Note: if instead of text being shown on the display, all the segments are on, you may need to decrease contrast value.
     */
    // lcd.setContrast(60); // 60 is the default value set by the driver
    
    lcd.print("Please Wait ...");
    delay(1000);
    lcd.clear();

    lcd.print("Hi there");
    lcd.println(":D");

    lcd.setCursor(0, 5);
    lcd.println("1 2 3 ...");
}

void loop() {}

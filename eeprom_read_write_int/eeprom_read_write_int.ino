#include<EEPROM.h>
const int eepromSize = 120;
const int baudEEPROMaddress = 64; /*eeprom adddress to store baudRate */


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(readIntFromEEPROM(baudEEPROMaddress));
}
void writeIntToEEPROM(int value, int address)
{
    if (readIntFromEEPROM(address) != value)
    {
        EEPROM.begin(eepromSize);
        EEPROM.put(address, value);
        EEPROM.commit();
    }
}

int readIntFromEEPROM(int address)
{
    int storedValue;
    EEPROM.begin(eepromSize);
    EEPROM.get(address, storedValue);
    return storedValue;
}
void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);

}

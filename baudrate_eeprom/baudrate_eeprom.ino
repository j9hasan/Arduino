#include <EEPROM.h>

// #define EEPROM_SIZE 0x5000  // Size of emulated EEPROM in bytes
const int eepromAddress = 65;  // Starting address for EEPROM operations

void writeIntToEEPROM(int value)
{
  EEPROM.begin(100);
  EEPROM.put(eepromAddress, value);
  EEPROM.commit();
}

int readIntFromEEPROM()
{
  int storedValue;
  EEPROM.begin(100);
  EEPROM.get(eepromAddress, storedValue);
  return storedValue;
}

void setup() {
  Serial.begin(115200);

  // Write an integer value to EEPROM
  // int valueToStore = 115200;
  // writeIntToEEPROM(valueToStore);
  writeIntToEEPROM(115200);
  Serial.println("Integer value stored in EEPROM.");
}

void loop() {
  // Your main program logic goes here
  // ...

  // Read the integer value from EEPROM
  // int storedValue = readIntFromEEPROM();

  Serial.println(readIntFromEEPROM());


  // Wait for a while before reading again
  delay(1000);
}

#include <SD.h>

const int chipSelect = 5; // Set your SD card chip select pin

void setup() {
  Serial.begin(115200);

  if (SD.begin(chipSelect)) {
    Serial.println("SD card initialized successfully");

    // Check if the folder exists
    if (!SD.exists("/scanData")) {
      Serial.println("scanData folder does not exist, creating...");

      // Create the folder
      if (SD.mkdir("/scanData")) {
        Serial.println("scanData folder created successfully");
      } else {
        Serial.println("Error creating scanData folder");
      }
    } else {
      Serial.println("scanData folder already exists");
    }
  } else {
    Serial.println("SD card initialization failed");
  }
}

void loop() {
  // Your main code here
}

#include <Arduino.h>
#include <WiFi.h>
#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

AudioFileSourceSD *file;
AudioGeneratorMP3 *mp3;
AudioFileSourceSD *source;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;
SPIClass SDSPI(VSPI);

void setup() {
  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_OFF);
  delay(500);

  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  SDSPI.begin(18, 19, 23); // SDSPI.begin(SCLK, MISO, MOSI);
  SDSPI.setFrequency(1000000);
  if(SD.begin(5, SDSPI)){
    Serial.println("SD initiated");
  }
  else{
    Serial.println(SD.begin(5, SDSPI));
  }
}




void loop() {
  delay(100);
}

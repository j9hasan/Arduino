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
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  SDSPI.begin(18, 19, 23);  // SDSPI.begin(SCLK, MISO, MOSI);
  SDSPI.setFrequency(1000000);
  SD.begin(5, SDSPI);
  delay(500);
  playMP3("/test.mp3");

}

void loop() {
  // playMP3("/shapeofyou.mp3");
  Serial.println("inside main loop");
  delay(2000);
}

void playMP3(char *filename) {
  file = new AudioFileSourceSD(filename);
  id3 = new AudioFileSourceID3(file);
  out = new AudioOutputI2S(0, 2, 8, -1);  // Output to builtInDAC
  out->SetOutputModeMono(true);
  out->SetGain(0.7);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(id3, out);
  while (mp3->isRunning()) {
    if (!mp3->loop()) {
      mp3->stop();
      delete mp3;
      delete id3;
      delete out;
      return;
    }
  }
}
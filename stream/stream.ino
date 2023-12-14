#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"

// #define I2S_DOUT      26  // connect to DAC pin DIN
// #define I2S_BCLK      27  // connect to DAC pin BCK
// #define I2S_LRC       25  // connect to DAC pin LCK

Audio audio(true, I2S_DAC_CHANNEL_BOTH_EN);

const char* ssid = "SOALIB2";
const char* password = "bangladesh123";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1500);
    Serial.println("connecting");
  }
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("connected");
  }
  // audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  // audio.setVolume(12);
  // audio.maxVolume();
  audio.connecttohost("http://s1.knixx.fm/dein_webradio_64.aac");  // 64 kbp/s aac+
  // audio.loop();
}

void loop() {
  delay(10);
}

void audio_info(const char* info) {
  Serial.print("info        ");
  Serial.println(info);
}
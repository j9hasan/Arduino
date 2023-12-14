#include <Arduino.h>
#include <WiFi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

AudioFileSourceSD *file;
AudioGeneratorMP3 *mp3;
AudioFileSourceID3 *id3;
AudioOutputI2S *out;

SPIClass SDSPI(VSPI);

bool isPlaying = false;
bool isPaused = false;
int currentTrack = 0;

// Pin definitions for buttons
const int playPauseButtonPin = 2;  // GPIO2
const int prevButtonPin = 3;       // GPIO3
const int nextButtonPin = 4;       // GPIO4

// Maximum number of tracks to handle
const int maxTracks = 100;
char *trackList[maxTracks];
int totalTracks = 0;

void playMP3(const char *filename) {
  file = new AudioFileSourceSD(filename);
  id3 = new AudioFileSourceID3(file);
  out = new AudioOutputI2S(0, 2, 8, -1); // Output to builtInDAC
  out->SetOutputModeMono(true);
  out->SetGain(0.7);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(id3, out);

  Serial.printf("Playing MP3 file: %s\n", filename);

  while (mp3->isRunning()) {
    if (!mp3->loop()) {
      mp3->stop();
      delete mp3;
      delete id3;
      delete out;
      return;
    }
    if (isPaused) {
      // Add logic for paused state
      vTaskDelay(100 / portTICK_PERIOD_MS);  // Adjust delay as needed
    }
  }
}

void playNextTrack() {
  currentTrack++;
  if (currentTrack >= totalTracks) {
    currentTrack = 0;
  }
  playMP3(trackList[currentTrack]);
}

void playPrevTrack() {
  currentTrack--;
  if (currentTrack < 0) {
    currentTrack = totalTracks - 1;
  }
  playMP3(trackList[currentTrack]);
}

void buttonTask(void *pvParameters) {
  pinMode(playPauseButtonPin, INPUT_PULLUP);
  pinMode(prevButtonPin, INPUT_PULLUP);
  pinMode(nextButtonPin, INPUT_PULLUP);

  while (1) {
    if (digitalRead(playPauseButtonPin) == LOW) {
      // Play/Pause button pressed
      if (isPlaying) {
        isPaused = !isPaused;
      } else {
        playMP3(trackList[currentTrack]);
        isPlaying = true;
      }
      delay(500);  // Debounce delay
    }

    if (digitalRead(nextButtonPin) == LOW) {
      // Next button pressed
      playNextTrack();
      delay(500);  // Debounce delay
    }

    if (digitalRead(prevButtonPin) == LOW) {
      // Previous button pressed
      playPrevTrack();
      delay(500);  // Debounce delay
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);  // Adjust delay as needed
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_OFF);
  delay(500);

  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  SDSPI.begin(18, 19, 23); // SDSPI.begin(SCLK, MISO, MOSI);
  SDSPI.setFrequency(1000000);
  SD.begin(5, SDSPI);

  // Dynamically populate the trackList array
  File root = SD.open("/");
  File entry = root.openNextFile();
  while (entry && totalTracks < maxTracks) {
    if (!entry.isDirectory() && strstr(entry.name(), ".mp3")) {
      // Concatenate "/" with the MP3 file name
      char *filePath = (char *)malloc(strlen(entry.name()) + 2); // +2 for "/" and null terminator
      if (filePath) {
        strcpy(filePath, "/");
        strcat(filePath, entry.name());
        trackList[totalTracks] = filePath;
        totalTracks++;
      }
    }
    entry = root.openNextFile();
  }
  root.close();

  xTaskCreate(buttonTask, "ButtonTask", 4096, NULL, 1, NULL);
}

void loop() {
  // The loop function is currently empty
}

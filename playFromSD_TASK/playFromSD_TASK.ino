//
// Demo for the ESP32Sound library
// https://github.com/ChrisVeigl/ESP32Sound
//
// This demo plays a music file from SD-Card.
// Put the file "sound1.wav" into the root folder of the SD-card.
//

#include <SD.h>
#include "ESP32Sound.h"

#define PLAYBACK_RATE 16000

const int buttonPin = 27;  // Replace with your button pin
volatile bool buttonPressed = false;

short i = 0;
bool taskHasRun = false;
TaskHandle_t myTask = NULL;
void setup() {
  Serial.begin(115200);
  Serial.println("Now initialising SD card!");
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  if (SD.cardType() == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.println("Now initialising sound system!");
  ESP32Sound.begin();
  ESP32Sound.setSoundVolume(15);
  ESP32Sound.playSound(SD, "/test1.wav");
  Serial.println("done");
  pinMode(buttonPin, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonInterrupt, FALLING);

  // xTaskCreate(myTaskFunction, "MyTask", 6 * 1024, NULL, 1, &myTask);
}


// void myTaskFunction(void *pvParameters) {
  // Task code goes here


  // while (1) {
    // // Your task's main loop code
    // ESP32Sound.playSound(SD, "/test1.wav");
    // vTaskDelay(5000 / portTICK_PERIOD_MS);
    // // Check some condition to decide whether to delete the task
    // if (!buttonPin) {
    //   // Delete the task
    //   SD.end();
    //   ESP32Sound.stopSound();
    //   myTask = NULL;
    //   vTaskDelete(myTask);
    // }

    // Rest of the loop code
  // }
// }






void loop() {
  delay(1000);
  Serial.println("loop");
}

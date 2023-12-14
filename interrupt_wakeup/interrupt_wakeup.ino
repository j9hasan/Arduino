#include <Arduino.h>

#define INTERRUPT_PIN_1 27
#define INTERRUPT_PIN_2 36
#define DEBOUNCE_DELAY 100 // Adjust as needed

RTC_DATA_ATTR unsigned long startTime = 0;
RTC_DATA_ATTR bool wokeUp = false;

void IRAM_ATTR handleInterrupt() {
  // Identify which pin triggered the interrupt
  int pin = digitalPinToInterrupt(INTERRUPT_PIN_1);
  if (digitalRead(INTERRUPT_PIN_2) == LOW) {
    pin = digitalPinToInterrupt(INTERRUPT_PIN_2);
  }

  // Software debounce
  delay(DEBOUNCE_DELAY);
  if (digitalRead(pin) == LOW) {
    // Handle the interrupt
    wokeUp = true;
    Serial.print("Interrupt happened on pin ");
    Serial.println(pin);
  }
}

void setup() {
  Serial.begin(115200);

  // Setup interrupt for pin 1
  pinMode(INTERRUPT_PIN_1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN_1), handleInterrupt, FALLING);

  // Setup interrupt for pin 2
  pinMode(INTERRUPT_PIN_2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN_2), handleInterrupt, FALLING);

  esp_sleep_enable_ext0_wakeup((gpio_num_t)INTERRUPT_PIN_2, LOW);  // Falling edge
  esp_sleep_enable_ext0_wakeup((gpio_num_t)INTERRUPT_PIN_1, LOW);  // Falling edge
}

void loop() {
  // If start time is not recorded, record it
  if (startTime == 0) {
    startTime = millis();
  }

  // Print "Hello" and do other tasks
  Serial.println("Hello");
  delay(500);  // Adjust as needed

  // Check if 1 minute has passed
  if ((millis() - startTime) > 10000) {
    Serial.print("Good night: ");
    esp_deep_sleep_start();
  }
}

#include <Arduino.h>

const int buttonPin = 27;  // GPIO pin for the button
volatile int rawPressCount = 0;  // Variable to store the raw press count
volatile int debouncedPressCount = 0;  // Variable to store the debounced press count
unsigned long lastDebounceTime = 0;  // Variable to store the last debounce time
unsigned long debounceDelay = 200;  // Debounce time in milliseconds

void IRAM_ATTR handleButtonPress() {
  // Get the current time
  unsigned long currentTime = millis();

  // Check if enough time has passed since the last button press
  if (currentTime - lastDebounceTime > debounceDelay) {
    rawPressCount++;  // Increment raw press count

    // Update the last debounce time
    lastDebounceTime = currentTime;
  }
}

void setup() {
  Serial.begin(115200);

  // Configure the button pin as an input with pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // Attach the interrupt to the button pin
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonPress, FALLING);
}

void loop() {
  // Print the raw and debounced press counts
  Serial.print("Raw Press Count: ");
  Serial.print(rawPressCount);
  Serial.print(" | Debounced Press Count: ");
  Serial.println(debouncedPressCount);

  // Update the debounced press count if a button press has been debounced
  if (rawPressCount > debouncedPressCount) {
    debouncedPressCount = rawPressCount;
  }

  // Check if the button has been released
  if (digitalRead(buttonPin) == HIGH) {
    // Reset press counts when the button is released
    rawPressCount = 0;
    debouncedPressCount = 0;
  }

  // Add additional logic or tasks as needed

  delay(700);  // Adjust the delay as needed for better performance
}

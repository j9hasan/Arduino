// Define the LEDC channel, timer, and output pin
const int ledcChannel = 0;
const int ledcTimer = 0;
const int ledcOutputPin = 26;  // GPIO26
const int frequency = 1000;    // Frequency of the tone in Hz
const int resolution = 8;      // LEDC PWM resolution
const int beepDuration = 200;  // Duration of each beep in milliseconds
const int pauseDuration = 200; // Pause duration between beeps in milliseconds
const int intervalBetweenBeeps = 2000; // Interval between beep sequences

unsigned long previousMillis = 0;
bool isBeeping = false;
int beepState = 0;

void setup() {
  // Set up the LEDC peripheral
  ledcSetup(ledcChannel, frequency, resolution);
  
  // Attach the LEDC channel to the output pin
  ledcAttachPin(ledcOutputPin, ledcChannel);
}

void loop() {
  beepBeep();
}

void beepBeep() {
  unsigned long currentMillis = millis();

  switch (beepState) {
    case 0:
      if (currentMillis - previousMillis >= intervalBetweenBeeps) {
        previousMillis = currentMillis;
        ledcWriteTone(ledcChannel, frequency);
        isBeeping = true;
        beepState = 1;
      }
      break;

    case 1:
      if (currentMillis - previousMillis >= beepDuration) {
        previousMillis = currentMillis;
        ledcWriteTone(ledcChannel, 0); // Stop the tone
        beepState = 2;
      }
      break;

    case 2:
      if (currentMillis - previousMillis >= pauseDuration) {
        previousMillis = currentMillis;
        ledcWriteTone(ledcChannel, frequency);
        beepState = 3;
      }
      break;

    case 3:
      if (currentMillis - previousMillis >= beepDuration) {
        previousMillis = currentMillis;
        ledcWriteTone(ledcChannel, 0); // Stop the tone
        isBeeping = false;
        beepState = 0;
      }
      break;
  }
}

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char *ssid = "ESPWIFI";
const char *password = "12345678";


const long utcOffsetInSeconds = 6 * 3600;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
TaskHandle_t timeTask = NULL;
void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize and synchronize time
  xTaskCreate(ntp_time_task, "timeTask", 2 * 1024, NULL, 2, &timeTask);
}

void loop() {
  // Update the timeClient
  Serial.print("main loop ");
  delay(1000);  // You can adjust the delay based on your requirements
}

void ntp_time_task(void *pvParameters) {


  timeClient.begin();

  while (1) {
    // Your task's main loop code
    if (WiFi.status() == WL_CONNECTED) {
      timeClient.update();
    } else {
      Serial.print("Wifi disconn. deleting time task");
      timeClient.end();
      vTaskDelete(timeTask);
      timeTask = NULL;
    }
    // Print the formatted date and time
    Serial.print("Current time: ");
    Serial.print(timeClient.getFormattedTime());
    Serial.println();
    //Check some condition to decide whether to delete the task
    if (WiFi.status() != WL_CONNECTED) {
    }
    //Rest of the loop code
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

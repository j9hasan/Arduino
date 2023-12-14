#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>

const char *ssid = "SOALIB2";
const char *password = "bangladesh123";
const char *ntpServer = "pool.ntp.org";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(250);
  //   Serial.print(".");
  // }
  // Serial.println("\nConnected to WiFi");

  // // Initialize NTP
  // timeClient.begin();

  // // Wait for the synchronization to complete
  // while (!timeClient.update()) {
  //   timeClient.forceUpdate();
  //   Serial.println("\Syncing to NTP Server");
  //   delay(100);
  // }

  // // Set the internal RTC of the ESP32
  // time_t rawTime = timeClient.getEpochTime();
  // struct tm *timeInfo = localtime(&rawTime);

  // // Set the system time
  // struct timeval now = { rawTime, 0 };
  // settimeofday(&now, nullptr);
  WiFi.disconnect();
  Serial.println(WiFi.status());
  
}

void loop() {
  // Get the current time from the internal RTC
  struct tm timeInfo;
  getLocalTime(&timeInfo);

  // Print current date and time
  Serial.print("Current time: ");
  Serial.print(timeInfo.tm_year + 1900);
  Serial.print('/');
  Serial.print(timeInfo.tm_mon + 1);
  Serial.print('/');
  Serial.print(timeInfo.tm_mday);
  Serial.print(" ");
  Serial.print(timeInfo.tm_hour);
  Serial.print(':');
  Serial.print(timeInfo.tm_min);
  Serial.print(':');
  Serial.println(timeInfo.tm_sec);

  delay(100);  // Wait for a second
}

#include <WiFi.h>
#include <HTTPClient.h>
#include <SD.h>

const char* ssid = "SOALIB2";
const char* password = "bangladesh123";
const char* url = "https://raw.githubusercontent.com/j9hasan/lvgl_8.3.6_esp_idf/master/lv7to8portingINSTR.txt";  // Replace with your file URL
const char* sdCardPath = "/sdcard";                                                                              // Replace with your desired SD card file path
const char* fileName = "/test_file1.txt";                                                                        // Replace with your desired file name

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize SD card
  if (!SD.begin(5)) {
    Serial.println("Failed to initialize SD card");
    return;
  }
  Serial.println("SD card initialized");

  // Check if directory exists, create if not
  if (!SD.exists(sdCardPath)) {
    Serial.println("Creating directory on SD card");
    if (SD.mkdir(sdCardPath)) {
      Serial.println("Directory created successfully");
    } else {
      Serial.println("Failed to create directory");
    }
  } else
    Serial.println("dir exist");
}

void loop() {
  // Create an HTTP client object
  HTTPClient http;

  // Specify the URL of the file to download
  http.begin(url);

  // Get the HTTP response code
  int httpResponseCode = http.GET();

  // Check if the request was successful
  if (httpResponseCode == HTTP_CODE_OK) {
    // Concatenate directory path and file name
    char filePath[50];  // Adjust the size based on your path length
    sprintf(filePath, "%s%s", sdCardPath, fileName);

    // Open a file on the SD card for writing
    File file = SD.open(filePath, FILE_WRITE);
    if (file) {
      Serial.println("Downloading.....");

      // Download file in chunks and write to the SD card
      WiFiClient* stream = http.getStreamPtr();
      const int bufferSize = 1024;  // Adjust the buffer size based on your requirements
      uint8_t buffer[bufferSize];
      int bytesRead;

      do {
        bytesRead = stream->readBytes(buffer, bufferSize);
        file.write(buffer, bytesRead);
      } while (bytesRead > 0);

      file.close();
      Serial.println("File downloaded and saved to SD card");
    } else {
      Serial.println("Error opening file on SD card for writing");
    }
  } else {
    Serial.print("HTTP request failed with error code: ");
    Serial.println(httpResponseCode);
  }

  // Disconnect the HTTP client
  http.end();

  // Wait for some time before the next iteration
  delay(60000);  // Wait for 1 minute before downloading again
}

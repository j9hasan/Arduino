#include <Arduino.h>
#include <vector>

// Define a struct
struct MyStruct {
  unsigned char type;        // 1 byte
  unsigned char ant;         // 1 byte
  signed char RSSI;          // 1 byte
  unsigned char count;       // 1 byte
  char EPCNUM[64];           // 64 bytes
  int epclen;                // 4 bytes
};

// Function to print MyStruct elements to Serial using Serial.printf()
void printStruct(const MyStruct& element) {
  Serial.printf("type = %d, ant = %d, RSSI = %d, Count = %d, EPCNUM = %s, EPClen = %d\n",
                element.type, element.ant, element.RSSI, element.count, element.EPCNUM, element.epclen);
}

void setup() {
  Serial.begin(115200);
  // Other setup code

  // Create a vector to store MyStruct instances
  std::vector<MyStruct> myVector;

  MyStruct myElement0 = {1, 2, 10, 20, "XTP205e845454d", 32};
  MyStruct myElement1 = {1, 2, 10, 20, "XTP205gwf845454d", 32};
  MyStruct myElement2 = {1, 2, 10, 20, "XTP205s845454d", 32};
  MyStruct myElement3 = {1, 2, 10, 20, "XTP20584rg5r454d", 32};
  MyStruct myElement4 = {1, 2, 10, 20, "XTP205845454d", 32};

  // Push the struct instances into the vector
  myVector.push_back(myElement0);
  myVector.push_back(myElement1);
  myVector.push_back(myElement2);
  myVector.push_back(myElement3);
  myVector.push_back(myElement4);

  // Print the vector elements
  for (const auto& element : myVector) {
    printStruct(element);
  }
}

void loop() {
  // Example usage

  // Add other loop code
  delay(1000);
}

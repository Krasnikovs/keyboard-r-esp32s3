



// #include <esp_now.h>
// #include <WiFi.h>
// #include <HIDTypes.h>
// #include <HIDKeyboardTypes.h>

// // Structure example to receive data
// // Must match the sender structure
// typedef struct struct_message {
//     char a[32];
//     int b;
//     float c;
//     float aX;
//     float aY;
//     float aZ;
//     bool d;
// } struct_message;

// // Create a struct_message called myData
// struct_message myData;

// // callback function that will be executed when data is received
// void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
//   memcpy(&myData, incomingData, sizeof(myData));
//   Serial.print("Bytes received: ");
//   Serial.println(len);
//   Serial.println(myData.aX);
//   Serial.println(myData.aY);
//   Serial.println(myData.aZ);
//   Serial.println();
// }
 
// void setup() {
//   // Initialize Serial Monitor
//   Serial.begin(115200);
  
//   // Set device as a Wi-Fi Station
//   WiFi.mode(WIFI_STA);

//   // Init ESP-NOW
//   if (esp_now_init() != ESP_OK) {
//     Serial.println("Error initializing ESP-NOW");
//     return;
//   }
  
//   // Once ESPNow is successfully Init, we will register for recv CB to
//   // get recv packer info
//   esp_now_register_recv_cb(OnDataRecv);
// }
 
// void loop() {
  
// }
#include <Arduino.h>
// cc:ba:97:12:08:1c
// #ifndef ARDUINO_USB_MODE
// #error This ESP32 SoC has no Native USB interface
// #elif ARDUINO_USB_MODE == 1
// // #warning This sketch should be used when USB is in OTG mode
// void setup() {
//   Serial.begin(115200);
// }
// void loop() {
//   Serial.println("Nothing");
// }
// #else


#include "USB.h"
#include "USBHIDMouse.h"
#include "USBHIDKeyboard.h"

// #include "/home/goodchair/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32s3/include/arduino_tinyusb/tinyusb/src/"

USBHIDKeyboard Keyboard;

int pinA = 4;

void setup() {
    // pinMode(pinA, INPUT_PULLUP);
    Serial.begin(115200);
    Keyboard.begin();
    USB.begin();
}

void loop() {
    // if (digitalRead(pinA) == LOW) {
    //     Keyboard.write('A');
    //     Serial.println("Run");
    //     delay(500);
    // }

    // Keyboard.write('A');
    Serial.println("Run");
    delay(500);
}
// #endif /* ARDUINO_USB_MODE */
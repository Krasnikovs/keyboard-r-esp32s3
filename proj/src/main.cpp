
#include <Arduino.h>


#include <esp_now.h>
#include <WiFi.h>
// #include <HIDTypes.h>
// #include <HIDKeyboardTypes.h>

// #include "USB.h"
// #include "USBHIDMouse.h"
// #include "USBHIDKeyboard.h"
#include <USB.h>
#include <USBHIDKeyboard.h>
#include <USBCDC.h>

USBHIDKeyboard Keyboard;
// USBCDC m_serial;
// ESPUSB *m_usb;

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[1];
    int b;
} struct_message;

// Create a struct_message called myData
struct_message myData;

char recData;
int new_data;
// void out(char simbol);
// static void
// usbEventCallback(void*            arg,
//                  esp_event_base_t event_base,
//                  int32_t          event_id,
//                  void*            event_data) {
//   if (event_base == ARDUINO_USB_EVENTS) {
//     arduino_usb_event_data_t* data = (arduino_usb_event_data_t*)event_data;
//     switch (event_id) {
//       case ARDUINO_USB_STARTED_EVENT:
//         m_serial.println("USB PLUGGED");
//         break;
//       case ARDUINO_USB_STOPPED_EVENT:
//         m_serial.println("USB UNPLUGGED");
//         break;
//       case ARDUINO_USB_SUSPEND_EVENT:
//         m_serial.printf("USB SUSPENDED: remote_wakeup_en: %u\n",
//                         data->suspend.remote_wakeup_en);
//         break;
//       case ARDUINO_USB_RESUME_EVENT:
//         m_serial.println("USB RESUMED");
//         break;

//       default:
//         break;
//     }
//   } else if (event_base == ARDUINO_USB_HID_EVENTS) {
//     arduino_usb_hid_event_data_t* data =
//       (arduino_usb_hid_event_data_t*)event_data;
//     switch (event_id) {
//       case ARDUINO_USB_HID_SET_PROTOCOL_EVENT:
//         m_serial.printf("HID SET PROTOCOL: %s\n",
//                         data->set_protocol.protocol ? "REPORT" : "BOOT");
//         break;
//       case ARDUINO_USB_HID_SET_IDLE_EVENT:
//         m_serial.printf("HID SET IDLE: %u\n", data->set_idle.idle_rate);
//         break;

//       default:
//         break;
//     }
//   }
// }



// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  // Serial.print("Bytes received: ");
  // Serial.println(len);
  // Serial.println(myData.a[0]);

  // Keyboard.press(myData.a[0]);
  recData = myData.a[0];
  new_data = myData.b;
  // Serial.println(myData.b);
  // Serial.println();
}

void setup() {

  // m_serial.onEvent(usbEventCallback);
  // Keyboard.onEvent(usbEventCallback);
  // USB.onEvent(usbEventCallback);

  Serial.begin(115200);
  // m_serial.begin(115200);
  
  while (!Serial) {
		delay(10);
	}
  Serial.println("Starting...");
  Serial.println("Initializing keyboard and usb...");
  USB.begin();
  // m_usb = &USB;
  // m_usb->begin();
  Keyboard.begin();
  delay(100);
  // Set device as a Wi-Fi Station

  Serial.println("Initializing wifi...");
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  delay(100);
  
  // // Once ESPNow is successfully Init, we will register for recv CB to
  // // get recv packer info
  // // esp_now_register_recv_cb(OnDataRecv);
  // esp_now_recv_cb_t(OnDataRecv);
  // esp_now_register_recv_cb(OnDataRecv);
  if(esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv)) == ESP_OK)
  {
    Serial.println("receive calback registered OK");
  }
  // esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
  Serial.println("Ready.");
}
 
void loop() {
  // memcpy(&myData, '\0', sizeof(myData));
  
  if (new_data == 2) {
    Keyboard.press(recData);
    delay(5);
    Keyboard.release(recData);
  }
  

  // esp_now_recv_info();
  // Serial.println("c");
  // 
  new_data = 0;
  delay(10);
}

// void out(char simbol) {
//   Keyboard.press(simbol);
//   // delay(1000);
// }


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
// }1bbbbbbbbbbba
// #else


// #include "USB.h"
// #include "USBHIDMouse.h"
// #include "USBHIDKeyboard.h"

// // #include "/home/goodchair/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32s3/include/arduino_tinyusb/tinyusb/src/"

// USBHIDKeyboard Keyboard;

// int pinA = 4;
// void setup() {
//     pinMode(0, INPUT_PULLUP);
//     Serial.begin(115200);
//     Keyboard.begin();
//     USB.begin();
// }

// void loop() {
//     // if (digitalRead(pinA) == LOW) {
//     //     Keyboard.write('A');
//     //     Serial.println("Run");
//     //     delay(500);
//     // }

    
// }
// #endif /* ARDUINO_USB_MODE */

// Build:Mar 27 2021
// rst:0xc (RTC_SW_CPU_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
// Saved PC:0x40376e8c
// SPIWP:0xee
// mode:DOUT, clock div:1
// load:0x3fce3808,len:0x41c
// load:0x403c9700,len:0x9a8
// load:0x403cc700,len:0x28d0
// entry 0x403c98b8
// E (95) cpu_start: Octal Flash option selected, but EFUSE not configured!

// abort() was called at PC 0x40376a6d on core 0


// Backtrace: 0x4037727e:0x3fceb260 0x4037a999:0x3fceb280 0x403801d9:0x3fceb2a0 0x40376a6d:0x3fceb320 0x403cd72f:0x3fceb350 0x403cd9ee:0x3fceb380 0x403c990d:0x3fceb4b0 0x40045c01:0x3fceb570 0x40043ab6:0x3fceb6f0 0x40034c45:0x3fceb710




// ELF file SHA256: a09f341d97c2cddb

// E (119) esp_core_dump_flash: Core dump flash config is corrupted! CRC=0x7bd5c66f instead of 0x0
// Rebooting...
// ESP-ROM:esp32s3-20210327
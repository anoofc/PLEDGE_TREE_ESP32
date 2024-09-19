#define DEBUG         1
#define DMX_BULB_NUM  40  // Number of bulbs in the DMX chain 

#include <Arduino.h>
#include "SparkFunDMX.h"
#include <BluetoothSerial.h>

SparkFunDMX dmx;
BluetoothSerial SerialBT;

uint8_t colors[][3] = {
  {255, 0, 0}, // Red
  {0, 255, 0}, // Green
  {0, 0, 255}, // Blue
  {255, 255, 0}, // Yellow
  {0, 255, 255}, // Cyan
  {255, 0, 255}, // Magenta
  {255, 255, 255}, // White
  {0, 0, 0} // Off
};

uint8_t bulb_count = 0;

void all_bulb_off() {
  for (int i = 1; i <= DMX_BULB_NUM*3; i++) {
    dmx.write(i, 0);
  }
  dmx.update();
}



void setup() {
  Serial.begin(9600);             // Initialize Serial Monitor
  SerialBT.begin("PLEDGE_TREE");  //Bluetooth device name
  dmx.initWrite(500);             // Initialize DMX Master
  all_bulb_off();                 // Turn off all bulbs
}

void loop() {
  
}


#define DEBUG         0  // Debug Mode
#define DMX_BULB_NUM  40  // Number of bulbs in the DMX chain 

#define   WARM  255, 180, 40
#define   OFF   0, 0, 0

#include  <Arduino.h>
#include  "SparkFunDMX.h"
#include  <BluetoothSerial.h>

uint8_t bulb_count = 0;

uint8_t animation_3[DMX_BULB_NUM] = {
  1,2,3,4,5,6,7,8,9,10,
  11,12,13,14,15,16,17,18,19,20,
  21,22,23,24,25,26,27,28,29,30,
  31,32,33,34,35,36,37,38,39,40
};
uint8_t animation_1[DMX_BULB_NUM] = {
  18, 5, 22, 7, 39, 11, 2, 26, 33, 12, 
  35, 21, 9, 3, 24, 17, 28, 14, 27, 4, 
  37, 20, 19, 36, 16, 6, 23, 1, 30, 38, 
  34, 32, 8, 40, 13, 25, 31, 15, 10, 29
};
uint8_t animation_2[DMX_BULB_NUM] = {
  6, 33, 10, 25, 2, 31, 17, 21, 36, 27,
  14, 19, 8, 1, 22, 4, 30, 38, 9, 39, 
  18, 12, 40, 35, 32, 3, 26, 23, 5, 29,
  11, 28, 7, 16, 24, 34, 13, 15, 37, 20
};

SparkFunDMX dmx;
BluetoothSerial SerialBT;

void write_color(uint8_t r, uint8_t g, uint8_t b, uint8_t bulb_id) {
  uint8_t channel_r = (bulb_id*3)-2; uint8_t channel_g = (bulb_id*3)-1; uint8_t channel_b = (bulb_id*3);
  dmx.write(channel_r, r); dmx.write(channel_g, g); dmx.write(channel_b, b);dmx.update(); dmx.update(); dmx.update();
  if (DEBUG){Serial.println("Channel R: "+String(channel_r)+"\t G: "+String(channel_g)+"\t B: "+String(channel_b));}
}


void all_bulb_off() {
  for (int i = 1; i <= DMX_BULB_NUM*3; i++) {
    dmx.write(i, 0);
  } 
  if (DEBUG){Serial.println("All Bulbs Off");} dmx.update();dmx.update();dmx.update();
}
void all_bulb_on() {
  for (int i = 1; i <= DMX_BULB_NUM; i++) {
    dmx.write((i*3)-2,255); dmx.write((i*3)-1,180); dmx.write(i*3,40);
  } if (DEBUG){Serial.println("All Bulbs On");} dmx.update();dmx.update();dmx.update();
}


void bulb_test(){
  for (int i = 1; i <= DMX_BULB_NUM; i++) {
    write_color(WARM, i);
    delay(500);
  }
}

void reset_bulb() {
  write_color(WARM, animation_1[bulb_count]);
  delay(1000);
  if (DEBUG){Serial.println("Max Bulb Reached");}
  Serial.println("RESET");
  for (int i=0; i<3; i++) {
    all_bulb_on();    delay(500);
    all_bulb_off();   delay(500);
  }
  for (int i = sizeof(animation_1); i >= 0; i--) {
    write_color(OFF, animation_1[i]);
    delay(250);
  }
  bulb_count = 0;
  if (DEBUG){Serial.println("Bulb Reset");}
}

void add_bulb() {
  if (DEBUG){Serial.println("BULB_COUNT: "+ String(bulb_count) + "\t BULB_ID: " +String(animation_1[bulb_count]) );}
  if (bulb_count == sizeof(animation_1)) { reset_bulb();}
  else {
    write_color(WARM, animation_1[bulb_count]);
    bulb_count++;
    if (DEBUG){Serial.println("Bulb Added");}
  }
}


void processData(char incoming) {
  if (incoming == 'A') {
    add_bulb();
  } else if (incoming == 'X') {
    all_bulb_on();
  } else if (incoming == 'Z') {
    bulb_count = 0;
    all_bulb_off();
  } else if (incoming == 'T') {
    bulb_test();
  } else {
    if (DEBUG){Serial.println("Invalid Command");}
  }
}

void readBTSerial() {
  if (SerialBT.available()) {
    char incoming = SerialBT.read();
    processData(incoming);
  }
}

void readSerial() {
  if (Serial.available()) {
    char incoming = Serial.read();
    processData(incoming);
  }
}


void setup() {
  Serial.begin(9600);             // Initialize Serial Monitor
  SerialBT.begin("PLEDGE_TREE");  //Bluetooth device name
  dmx.initWrite(121);             // Initialize DMX Master
  all_bulb_off();                 // Turn off all bulbs
}

void loop() {
  // readSerial();
  readBTSerial();              // Read Bluetooth Serial

}


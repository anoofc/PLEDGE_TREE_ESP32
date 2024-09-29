#define DEBUG         0  // Debug Mode
#define DMX_BULB_NUM  40  // Number of bulbs in the DMX chain 

#define   WARM  255, 180, 40
#define   OFF   0, 0, 0

#include  <Arduino.h>
#include  "SparkFunDMX.h"
#include  <BluetoothSerial.h>

uint8_t bulb_count_1 = 0;
uint8_t bulb_count_2 = 0;
uint8_t bulb_count_3 = 0;

uint8_t animation_1[10] = {
  1,2,3,4,5,6,7,8,9,10
};
uint8_t animation_2[10] = {
  11,12,13,14,15,16,17,18,19,20
};
uint8_t animation_3[20] = {
  21,22,23,24,25,26,27,28,29,30,
  31,32,33,34,35,36,37,38,39,40
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

void set_1_all_off() {
  for (int i = 1; i <= 10*3; i++) {
    dmx.write(i, 0);
  } 
  if (DEBUG){Serial.println("Set 1 Bulbs Off");} dmx.update();dmx.update();dmx.update();
}
void set_1_all_on() {
  for (int i = 1; i <= 10; i++) {
    dmx.write((i*3)-2,255); dmx.write((i*3)-1,180); dmx.write(i*3,40);
  } if (DEBUG){Serial.println("Set 1 Bulbs On");} dmx.update();dmx.update();dmx.update();
}

void set_2_all_off() {
  for (int i = 11; i <= 20*3; i++) {
    dmx.write(i, 0);
  } 
  if (DEBUG){Serial.println("Set 2 Bulbs Off");} dmx.update();dmx.update();dmx.update();
}
void set_2_all_on() {
  for (int i = 11; i <= 20; i++) {
    dmx.write((i*3)-2,255); dmx.write((i*3)-1,180); dmx.write(i*3,40);
  } if (DEBUG){Serial.println("Set 2 Bulbs On");} dmx.update();dmx.update();dmx.update();
}

void set_3_all_off() {
  for (int i = 21; i <= 40*3; i++) {
    dmx.write(i, 0);
  } 
  if (DEBUG){Serial.println("Set 3 Bulbs Off");} dmx.update();dmx.update();dmx.update();
}
void set_3_all_on() {
  for (int i = 21; i <= 40; i++) {
    dmx.write((i*3)-2,255); dmx.write((i*3)-1,180); dmx.write(i*3,40);
  } if (DEBUG){Serial.println("Set 3 Bulbs On");} dmx.update();dmx.update();dmx.update();
}


void bulb_test(){
  for (int i = 1; i <= DMX_BULB_NUM; i++) {
    write_color(WARM, i);
    delay(500);
  }
}

void reset_bulb_set1() {
  if (DEBUG){Serial.println("Set 1 Max Bulb Reached");}
  Serial.println("RESET SET 1");
  for (int i=0; i<3; i++) {
    set_1_all_on();    delay(500);
    set_1_all_off();   delay(500);
  }
  for (int i = sizeof(animation_1)-1; i >= 0; i--) {
    write_color(OFF, animation_1[i]);
    delay(250);
  }
  bulb_count_1 = 0;
  if (DEBUG){Serial.println("Bulb Set 1 Reset");}
}

void reset_bulb_set2() {
  if (DEBUG){Serial.println("Set 2 Max Bulb Reached");}
  Serial.println("RESET SET 2");
  for (int i=0; i<3; i++) {
    set_2_all_on();    delay(500);
    set_2_all_off();   delay(500);
  }
  for (int i = sizeof(animation_2)-1; i >= 0; i--) {
    write_color(OFF, animation_2[i]);
    delay(250);
  }
  bulb_count_2 = 0;
  if (DEBUG){Serial.println("Bulb Set 2 Reset");}
}

void reset_bulb_set3() {
  if (DEBUG){Serial.println("Set 3 Max Bulb Reached");}
  Serial.println("RESET SET 3");
  for (int i=0; i<3; i++) {
    set_3_all_on();    delay(500);
    set_3_all_off();   delay(500);
  }
  for (int i = sizeof(animation_3)-1; i >= 0; i--) {
    write_color(OFF, animation_3[i]);
    delay(250);
  }
  bulb_count_3 = 0;
  if (DEBUG){Serial.println("Bulb Set 3 Reset");}
}

void addSet1(){
  if (DEBUG){Serial.println("BULB_COUNT: "+ String(bulb_count_1) + "\t BULB_ID: " +String(animation_1[bulb_count_1]) );}
  if (bulb_count_1 < sizeof(animation_1)) {
    write_color(WARM, animation_1[bulb_count_1]);
    bulb_count_1++;
    if (DEBUG){Serial.println("Bulb Added");}
  }
  if (bulb_count_1 == sizeof(animation_1)) { delay(1000); reset_bulb_set1();}
}

void addSet2(){
  if (DEBUG){Serial.println("BULB_COUNT: "+ String(bulb_count_2) + "\t BULB_ID: " + String(animation_2[bulb_count_2]) );}
  if (bulb_count_2 <  sizeof(animation_2)) {
    write_color(WARM, animation_2[bulb_count_2]);
    bulb_count_2++;
    if (DEBUG){Serial.println("Bulb Added");}
  }
  if (bulb_count_2 == sizeof(animation_2)) { delay(1000); reset_bulb_set2();}
}

void addSet3(){
  if (DEBUG){Serial.println("BULB_COUNT: "+ String(bulb_count_3) + "\t BULB_ID: " +String(animation_3[bulb_count_3]) );}
  if (bulb_count_3 < sizeof(animation_3)) {
    write_color(WARM, animation_3[bulb_count_3]);
    bulb_count_3++;
    if (DEBUG){Serial.println("Bulb Added");}
  }
  if (bulb_count_3 == sizeof(animation_3)) { delay(1000); reset_bulb_set3();}
}

void processData(char incoming) {
  if (incoming == 'A') {
    addSet1();
  } else if (incoming == 'B'){
    addSet2();
  } else if (incoming == 'C'){
    addSet3();
  } else if (incoming == 'X') {
    all_bulb_on();
  } else if (incoming == 'Z') {
    bulb_count_1 = 0;
    bulb_count_2 = 0;
    bulb_count_3 = 0;
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


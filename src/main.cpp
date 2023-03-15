#include <Arduino.h>
#include <U8g2lib.h>

#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display

#define bar_num 32
byte recievedData[bar_num];
uint8_t values[bar_num] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0};

void setup(void) {
  Serial.begin(115200);
  u8g2.begin();
}


void drawUpdate(uint8_t val[bar_num]){ 
    for (int i = 0; i < bar_num; i++){
      u8g2.drawBox(i*4, 0, 2, 1+val[i]);
  }
}

void recieveData(){
  for(int j = 0; j < bar_num; j++){
    recievedData[j] = Serial.read();
    values[j] = recievedData[j]*0.25;
  }
}

void loop(void) {
  u8g2.clearBuffer();
  
  if(Serial.available()){
    recieveData();
  }   

  drawUpdate(values);
  u8g2.sendBuffer();  
  delay(1);
// inputString = ""; //clear input
}
#include "NKP_V2.h"

void setup() {
  NKP_V2();
  wait();
  set_IMU();
}

void loop() {
  display.clearDisplay();
  display.setTextSize(1);      
  display.setCursor(30, 0);        
  display.println(F("Read angle"));
  display.setCursor(0, 15);            
  display.println(F("X = "));
  display.setCursor(38, 15);            
  display.println(Read_angle(0));
  display.setCursor(0, 30);            
  display.println(F("Y = "));
  display.setCursor(38, 30);             
  display.println(Read_angle(1));
  display.setCursor(0, 45);             
  display.println(F("Z = "));
  display.setCursor(38, 45);             
  display.println(Read_angle(2));
  display.display();
  delay(100);
}

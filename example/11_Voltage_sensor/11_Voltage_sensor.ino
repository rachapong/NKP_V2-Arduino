#include "NKP_V2.h"

void setup() {
  NKP_V2();
  wait();
}

void loop() {
    display.clearDisplay();
  display.setTextSize(1);      
  display.setCursor(30, 0);        
  display.println(F("Read Voltage"));
  display.setCursor(0, 15);            
  display.println(F("v = "));
  display.setCursor(38, 15);            
  display.println(Volt_input());
  display.display();
  delay(50);
  }

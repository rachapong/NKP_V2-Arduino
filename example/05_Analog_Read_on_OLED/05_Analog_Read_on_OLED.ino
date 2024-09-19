#include "NKP_V2.h"

void setup() {
  NKP_V2();             
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  display.clearDisplay();
  display.setTextSize(1);      
  display.setCursor(30, 0);        
  display.println(F("Read ADC"));
  display.setCursor(0, 15);            
  display.println(F("A1 = "));
  display.setCursor(38, 15);            
  display.println(ADC(1));
  display.setCursor(0, 30);            
  display.println(F("A2 = "));
  display.setCursor(38, 30);             
  display.println(ADC(2));
  display.setCursor(0, 45);             
  display.println(F("A3 = "));
  display.setCursor(38, 45);             
  display.println(ADC(3));
  display.display();
  delay(100);
}

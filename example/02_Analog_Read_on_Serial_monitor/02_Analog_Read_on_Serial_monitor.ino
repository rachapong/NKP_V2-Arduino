#include "NKP_V2.h"

void setup() {
  Serial.begin(119200);
  NKP_V2();
  
}

void loop() {
  Serial.print("TEST");
  Serial.print(" analog Read A1 = ");
  Serial.println(ADC(1));
  delay(100);
}

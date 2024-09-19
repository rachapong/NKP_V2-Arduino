#include "NKP_V2.h"

void setup() {
  Serial.begin(119200);
  NKP_V2();

  beep(1000);

  
}

void loop() {
  buzzer(100,500);
  buzzer(500,200);
  buzzer(1000,100);
}

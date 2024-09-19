#include "NKP_V2.h"

void setup() {
  NKP_V2();
  pinMode(14,OUTPUT);          //ตั้งค่า pin = (A7) 14 เป็น OUTPUT
}

void loop() {
  digitalWrite(14,HIGH);
  delay(1000);
  digitalWrite(14,0);
  delay(1000);
}

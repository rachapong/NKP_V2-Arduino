#include "NKP_V2.h"

void setup() {
  NKP_V2();
  wait();
}

void loop() {
  motor(1,50);                        //motor(ช่องของมอเตอร์  , ความเร็ว หน่วยเป็น %)
  motor(2,50);
  motor(3,50);
  motor(4,50);
  motor(5,50);
  motor(6,50);
  delay(1000);
  motor(1,100);
  motor(2,100);
  motor(3,100);
  motor(4,100);
  motor(5,100);
  motor(6,100);
  delay(1000);
  ao();         //motor_stop();
  delay(1000);
  motor(1,-50);
  motor(2,-50);
  motor(3,-50);
  motor(4,-50);
  motor(5,-50);
  motor(6,-50);
  delay(1000);
  motor(1,-100);
  motor(2,-100);
  motor(3,-100);
  motor(4,-100);
  motor(5,-100);
  motor(6,-100);
  delay(1000);
  ao();
  delay(1000);
}

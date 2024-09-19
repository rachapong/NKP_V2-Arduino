#include "NKP_V2.h"

void setup() {
  NKP_V2();
  servo(0,90);
  wait();
}

void loop() {

  servo(1,90);
  servo(2,90);
  servo(3,90);
  servo(4,90);
  servo(5,90);
  delay(1000);
  
  servo(1,0);
  servo(2,0);
  servo(3,0);
  servo(4,0);
  servo(5,0);
  delay(1000);

  servo(1,180);
  servo(2,180);
  servo(3,180);
  servo(4,180);
  servo(5,180);
  delay(1000);
}

#include "NKP_V2.h"
void readIMU(){
  for(int i =0;i<6;i++){
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
  delay(50);
  }
}
void setup() {
  NKP_V2();
  set_IMU();
  wait();
  
}

void loop() {
  motor(1,50);
  motor(2,50);
  motor(3,50);
  motor(4,50);
  motor(5,50);
  motor(6,50);
  readIMU();    // delay(1000);
  motor(1,100);
  motor(2,100);
  motor(3,100);
  motor(4,100);
  motor(5,100);
  motor(6,100);
  readIMU();
  ao();         //motor_stop();
  readIMU();    // delay(1000);
  motor(1,-50);
  motor(2,-50);
  motor(3,-50);
  motor(4,-50);
  motor(5,-50);
  motor(6,-50);
  readIMU();    // delay(1000);
  motor(1,-100);
  motor(2,-100);
  motor(3,-100);
  motor(4,-100);
  motor(5,-100);
  motor(6,-100);
  readIMU();
  ao();
  readIMU();  // delay(1000);



}

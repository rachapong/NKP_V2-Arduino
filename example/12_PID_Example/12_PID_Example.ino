#include <NKP_V2.h>

void setup() {
  NKP_V2();
  Serial.begin(115200);
  wait();
  PID_NumPin = 4;
  PID_set_Pin(1,2,3,4,0,0,0,0);
  PID_set_Max(4095,4095,4095,4095,4095,4095,4095,4095);
  PID_set_Min(100,100,100,100,100,100,100,100);
  // setSensorMax((const uint16_t[]){2400, 4001,4002,3500});
  // setSensorMin((const uint16_t[]){300, 301, 302, 303});
  // for (int i = 0; i < 3; i++) {
  //   for(int l = 0;l<300;l++){
  //     setCalibrate();
  //     delay(1);
  //     motor(1,30);
  //     motor(2,30);
  //   }
  //   aot(100);
  //   for(int l = 0;l<300;l++){
  //     setCalibrate();
  //     delay(1);
  //     motor(1,-30);
  //     motor(2,-30);
  //   }aot(100);

  //   for(int l = 0;l<200;l++){
  //     setCalibrate();
  //     delay(1);
  //     motor(1,-30);
  //     motor(2,-30);
  //   }aot(100);
  //   for(int l = 0;l<300;l++){
  //     setCalibrate();
  //     delay(1);
  //     motor(1,30);
  //     motor(2,30);
  //   }
  //   aot(100);

  // }
  // aot(100);
  // for (uint8_t i = 0; i < numSensor; i++)
  // {
  //   Serial.print(ReadSensorMinValue(i));
  //   Serial.print(' ');
  // }
  // Serial.println();
  // for (uint8_t i = 0; i < numSensor; i++)
  // {
  //   Serial.print(ReadSensorMaxValue(i));
  //   Serial.print(' ');
  // }
  //wait();
}

void loop() {

  // display.clearDisplay();
  // display.setTextSize(1);      
  // display.setCursor(30, 0);        
  // display.println(F("Read position"));         
  // display.setCursor(38, 15);            
  // display.println(readline());
  // display.display();
  // delay(50);


 //Run_PID(ความเร็ว, KP, KD);
   Run_PID(30, 0.5, 5);
}

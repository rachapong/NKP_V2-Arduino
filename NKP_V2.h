#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "NKP_V2Motor_drive.h"
#include "NKP_V2Servo_lib.h"
#include "NKP_V2Interrupt.h"
#include "MPU6050_tockn.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define A1 39
#define A2 36
#define A3 34
#define A4 32
#define A5 25
#define A6 26
#define A7 14
#define A12 33
#define A13 33
#define A14 27

MPU6050 mpu6050(Wire);
Adafruit_SSD1306 display(128, 64, &Wire, -1);



int PID_NumPin = 3;
int Front_color = 0;
int Front_sensitive = 20;
int PID_SetupPin[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int PID_Min[] = { 10, 10, 10, 10, 10, 10, 10, 10 };
int PID_Max[] = { 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000 };
float errors = 0;
float output = 0;
float integral = 0;
float derivative = 0;
float previous_error = 0;
uint16_t state_on_Line = 0;
uint32_t _lastPosition;
bool first_state_for_calribrate = 0;

int PID_NumPin_B = 3;
int Black_color = 0;
int Black_sensitive = 20;
int PID_SetupPin_B[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int PID_Min_B[] = { 10, 10, 10, 10, 10, 10, 10, 10 };
int PID_Max_B[] = { 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000 };
float errors_B = 0;
float output_B = 0;
float integral_B = 0;
float derivative_B = 0;
float previous_error_B = 0;
uint16_t state_on_Line_B = 0;
uint32_t _lastPosition_B;
bool first_state_for_calribrate_B = 0;

int state_IMU = 0;
int state_boot = 0;

int ADC(int _pin){
    if(_pin == 1){return analogRead(36);}
    else if(_pin == 2){return analogRead(39);}
    else if(_pin == 3){return analogRead(34);}
    else if(_pin == 4){return analogRead(32);}
    else if(_pin == 5){return analogRead(25);}
    else if(_pin == 6){return analogRead(26);}
    else if(_pin == 7){return analogRead(14);}
    
    else if(_pin == 12){return analogRead(35);}
    else if(_pin == 13){return analogRead(33);}
    else if(_pin == 14){return analogRead(27);}

    else if(_pin == 8){return ADC_Read(0);}
    else if(_pin == 9){return ADC_Read(2);}
    else if(_pin == 10){return ADC_Read(5);}
    else if(_pin == 11){return ADC_Read(6);}
    else if(_pin == 15){return ADC_Read(1);}
    else if(_pin == 16){return ADC_Read(4);}
    else if(_pin == 17){return ADC_Read(7);}
  
}


void NKP_V2() {
  analogReadResolution(12);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(115200);
  pinMode(13, INPUT);
  // if (tcs.begin()) {
  //    Serial.println("Found sensor");
  // }
  
  if(ADC_Read(0) == 0 and ADC_Read(1) == 0 and ADC_Read(2) == 0 and ADC_Read(4) == 0 and ADC_Read(5) == 0 and ADC_Read(6) == 0 and ADC_Read(7) == 0){
    select_conection_i2c = 1;
    Wire1.begin(16,17);
  }
  delay(200);
  motor_control(14,0);
}


// int ADC(int _pin) {
//   if (_pin == 1) {
//     return analogRead(36);
//   } else if (_pin == 2) {
//     return analogRead(39);
//   } else if (_pin == 3) {
//     return analogRead(34);
//   } else if (_pin == 4) {
//     return analogRead(32);
//   } else if (_pin == 5) {
//     return analogRead(25);
//   } else if (_pin == 6) {
//     return analogRead(26);
//   } else if (_pin == 7) {
//     return analogRead(14);
//   }

//   else if (_pin == 12) {
//     return analogRead(35);
//   } else if (_pin == 13) {
//     return analogRead(33);
//   } else if (_pin == 14) {
//     return analogRead(27);
//   }

//   else if (_pin == 8) {
//     return ADC_inExtension(0);
//   } else if (_pin == 9) {
//     return ADC_inExtension(2);
//   } else if (_pin == 10) {
//     return ADC_inExtension(5);
//   } else if (_pin == 11) {
//     return ADC_inExtension(6);
//   } else if (_pin == 15) {
//     return ADC_inExtension(1);
//   } else if (_pin == 16) {
//     return ADC_inExtension(4);
//   } else if (_pin == 17) {
//     return ADC_inExtension(7);
//   }
// }


void set_IMU() {
  delay(500);
  display.clearDisplay();
  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(30, 15);             // Start at top-left corner
  display.println(F("IMU_Calibrat"));
  display.setCursor(40, 30);             // Start at top-left corner
  display.println(F("3 Second"));
  display.setCursor(38, 45);             // Start at top-left corner
  display.println(F("Don't Move"));
  display.display();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  mpu6050.update();
  if ((1000 + mpu6050.getAngleX()) > 1100 || (1000 + mpu6050.getAngleX()) < 900 || (1000 + mpu6050.getAngleY()) > 1100 || (1000 + mpu6050.getAngleY()) < 900 || (1000 + mpu6050.getAngleZ()) > 1100 || (1000 + mpu6050.getAngleZ()) < 900) {
    mpu6050.calcGyroOffsets(true);
    mpu6050.update();
  }
  display.clearDisplay();
  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0, 0);             // Start at top-left corner
  display.println(F("Angle X ="));
  display.setCursor(65, 0);             // Start at top-left corner
  display.println(1000 + mpu6050.getAngleX());
  display.setCursor(0, 17);             // Start at top-left corner
  display.println(F("Angle Y ="));
  display.setCursor(65, 17);             // Start at top-left corner
  display.println(1000 + mpu6050.getAngleY());
  display.setCursor(0, 35);             // Start at top-left corner
  display.println(F("Angle Z ="));
  display.setCursor(65, 35);             // Start at top-left corner
  display.println(1000 + mpu6050.getAngleZ());
  display.display();
  delay(700);
  state_IMU = 1;
}
int Read_angle(int angle_) {

  if (state_IMU == 0) {
    set_IMU();
  } else {
    mpu6050.update();
    if (angle_ == 0) {
      return 1000 + mpu6050.getAngleX();
    } else if (angle_ == 1) {
      return 1000 + mpu6050.getAngleY();
    } else if (angle_ == 2) {
      return 1000 + mpu6050.getAngleZ();
    }
  }
}
void buzzer(int freq, int timr_delay) {
  pinMode(12, OUTPUT);
  ledcAttachChannel(12,5000,8,7);
  
  // ledcSetup(7, 5000, 8);
  // ledcAttachPin(12, 7);
  ledcWriteTone(7, freq);
  delay(timr_delay);
}


void beep() {
  buzzer(1000, 200);
  buzzer(0, 200);
}
void beep_on() {
  buzzer(1000, 200);
}
void beep_off() {
  buzzer(0, 200);
}
void beep(int _delay) {
  buzzer(1000, _delay);
  buzzer(0, 1);
}

// float Volt_input() {
//   return (((float)ADC_inExtension(9) * (3.3 / 4095.0) * 5.05));
//   //return 0;
// }

void wait() {
  int state_sw0 = 0;
  pinMode(13, INPUT);
  pinMode(0, INPUT);
  display.clearDisplay();
  display.setTextSize(2);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(30, 0);             // Start at top-left corner
  display.println(F("NKP_V2"));
  display.display();
  delay(200);
  display.setTextSize(1);
  while (digitalRead(13) == 1) {
    while(digitalRead(0) == 0){
      state_boot +=1;
      if(state_boot >1)state_boot = 0;
      while(digitalRead(0) == 0);
    }
    if (state_boot == 0) {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println(F("A1="));
      display.setCursor(28, 0);
      display.println(ADC(1));
      display.setCursor(65, 0);
      display.println(F("A2="));
      display.setCursor(93, 0);
      display.println(ADC(2));
      display.setCursor(0, 12);
      display.println(F("A3="));
      display.setCursor(28, 12);
      display.println(ADC(3));
      display.setCursor(65, 12);
      display.println(F("A4="));
      display.setCursor(93, 12);
      display.println(ADC(4));
      display.setCursor(0, 24);
      display.println(F("A5="));
      display.setCursor(28, 24);
      display.println(ADC(5));
      display.setCursor(65, 24);
      display.println(F("A6="));
      display.setCursor(93, 24);
      display.println(ADC(6));
      display.setCursor(0, 36);
      display.println(F("A7="));
      display.setCursor(28, 36);
      display.println(ADC(7));
      display.setCursor(65, 36);
      display.println(F("A8="));
      display.setCursor(93, 36);
      display.println(ADC(8));
      display.setCursor(0, 48);
      display.println(F("Press boot Switch to Read Analog CH A9-A17"));
      display.display();
      delay(100);
    } else {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println(F("A9="));
      display.setCursor(28, 0);
      display.println(ADC(9));
      display.setCursor(65, 0);
      display.println(F("A10="));
      display.setCursor(93, 0);
      display.println(ADC(10));
      display.setCursor(0, 12);
      display.println(F("A11="));
      display.setCursor(28, 12);
      display.println(ADC(11));
      display.setCursor(65, 12);
      display.println(F("A12="));
      display.setCursor(93, 12);
      display.println(ADC(12));
      display.setCursor(0, 24);
      display.println(F("A13="));
      display.setCursor(28, 24);
      display.println(ADC(13));
      display.setCursor(65, 24);
      display.println(F("A14="));
      display.setCursor(93, 24);
      display.println(ADC(14));
      display.setCursor(0, 36);
      display.println(F("A15="));
      display.setCursor(28, 36);
      display.println(ADC(15));
      display.setCursor(65, 36);
      display.println(F("A16="));
      display.setCursor(93, 36);
      display.println(ADC(16));
      display.setCursor(0, 48);
      display.println(F("A17="));
      display.setCursor(28, 48);
      display.println(ADC(17));
      display.setCursor(65, 48);
      display.println(F("Volt="));
      display.setCursor(93, 48);
      display.println(Volt_input());
      display.display();
      delay(100);
    }
     
  }
  beep();
  display.clearDisplay();
  display.display();
  delay(500);
}
void IO15(){
  wait();
}
void sw1(){
  wait();
}
void SW1(){
  wait();
}


// float Read_Color_TCS(int color_of_sensor){
//   uint16_t clearcol_lib, red_lib, green_lib, blue_lib;
//  float average_lib, r_lib, g_lib, b_lib;
//  //delay(100); // Farbmessung dauert c. 50ms
//  tcs.getRawData(&red_lib, &green_lib, &blue_lib, &clearcol_lib);
//  average_lib = (red_lib+green_lib+blue_lib)/3;
//  r_lib = red_lib/average_lib;
//  g_lib = green_lib/average_lib;
//  b_lib = blue_lib/average_lib;
//  if(color_of_sensor == 0){
//   return r_lib*100;
//  }
//  else if(color_of_sensor == 1){
//   return g_lib*100;
//  }
//   else if(color_of_sensor == 2){
//   return b_lib*100;
//  }
// }
void set_Front_color() {
}
void PID_set_Min(int S0, int S1, int S2, int S3, int S4, int S5, int S6, int S7) {
  PID_Min[0] = S0;
  PID_Min[1] = S1;
  PID_Min[2] = S2;
  PID_Min[3] = S3;
  PID_Min[4] = S4;
  PID_Min[5] = S5;
  PID_Min[6] = S6;
  PID_Min[7] = S7;
}
void PID_set_Max(int S0, int S1, int S2, int S3, int S4, int S5, int S6, int S7) {
  PID_Max[0] = S0;
  PID_Max[1] = S1;
  PID_Max[2] = S2;
  PID_Max[3] = S3;
  PID_Max[4] = S4;
  PID_Max[5] = S5;
  PID_Max[6] = S6;
  PID_Max[7] = S7;
}
void PID_set_Pin(int S0, int S1, int S2, int S3, int S4, int S5, int S6, int S7) {
  PID_SetupPin[0] = S0;
  PID_SetupPin[1] = S1;
  PID_SetupPin[2] = S2;
  PID_SetupPin[3] = S3;
  PID_SetupPin[4] = S4;
  PID_SetupPin[5] = S5;
  PID_SetupPin[6] = S6;
  PID_SetupPin[7] = S7;
}
void setCalibrate(int round) {
  //display.clear();
  //display.setFont(ArialMT_Plain_24);
  ////display.drawString(0,0,"Front Sensor");
  //display.drawString(0,25,"  Calribrate  ");
  //display.//display();
  if (first_state_for_calribrate == 0) {
    for (uint8_t i = 0; i < PID_NumPin; i++) {
      PID_Max[i] = 0;
      PID_Min[i] = 4095;
    }
    first_state_for_calribrate = 1;
  }
  for (int roundOfCalribtate = 0; roundOfCalribtate < round; roundOfCalribtate++) {
    for (uint8_t i = 0; i < PID_NumPin; i++) {
      if (ADC(PID_SetupPin[i]) > PID_Max[i] || PID_Max[i] >= 4095) {
        PID_Max[i] = ADC(PID_SetupPin[i]);
        if (PID_Max[i] > 4095) PID_Max[i] = 4095;
      }
    }
    for (uint8_t i = 0; i < PID_NumPin; i++) {
      if (ADC(PID_SetupPin[i]) < PID_Min[i] || PID_Min[i] == 0) {
        PID_Min[i] = ADC(PID_SetupPin[i]);
        if (PID_Min[i] < 0) PID_Min[i] = 0;
      }
    }
    delay(1);
  }
  //display.clear();
}
int ReadSensorMinValue(uint8_t _Pin) {
  return PID_Min[_Pin];
}
int ReadSensorMaxValue(uint8_t _Pin) {
  return PID_Max[_Pin];
}

int readline() {
  bool onLine = false;
  long avg = 0;
  long sum = 0;
  for (uint8_t i = 0; i < PID_NumPin; i++) {
    long value;
    if (Front_color == 0) {
      value = map(ADC(PID_SetupPin[i]), PID_Min[i], PID_Max[i], 100, 0);
    } else {
      value = map(ADC(PID_SetupPin[i]), PID_Min[i], PID_Max[i], 0, 100);
    }

    value = constrain(value, 0, 100);
    if (value > Front_sensitive) {
      onLine = true;
    }
    if (value > 5) {
      avg += (long)value * (i * 100)+50;
      sum += value;
    }
  }
  if (!onLine) {
    if (_lastPosition < ((PID_NumPin - 1) * 100) / 2) {
      return 0;
    } else {
      return ((PID_NumPin - 1) * 100);
    }
  }
  _lastPosition = avg / sum;
  return _lastPosition;
}
void Run_PID(int RUN_PID_speed, float RUN_PID_KP, float RUN_PID_KD) {

  int present_position = readline();
  int setpoint = ((PID_NumPin - 1) * 100) / 2;
  errors = present_position - setpoint;
  integral = integral + errors;
  derivative = (errors - previous_error);
  output = RUN_PID_KP * errors + RUN_PID_KD * derivative;

  int m1Speed = RUN_PID_speed + output;
  int m2Speed = RUN_PID_speed - output;
  motor(1, m1Speed);
  motor(2, m2Speed);
  delay(1);
  previous_error = errors;
}

void PID_set_Min_B(int S0, int S1, int S2, int S3, int S4, int S5, int S6, int S7) {
  PID_Min_B[0] = S0;
  PID_Min_B[1] = S1;
  PID_Min_B[2] = S2;
  PID_Min_B[3] = S3;
  PID_Min_B[4] = S4;
  PID_Min_B[5] = S5;
  PID_Min_B[6] = S6;
  PID_Min_B[7] = S7;
}
void PID_set_Max_B(int S0, int S1, int S2, int S3, int S4, int S5, int S6, int S7) {
  PID_Max_B[0] = S0;
  PID_Max_B[1] = S1;
  PID_Max_B[2] = S2;
  PID_Max_B[3] = S3;
  PID_Max_B[4] = S4;
  PID_Max_B[5] = S5;
  PID_Max_B[6] = S6;
  PID_Max_B[7] = S7;
}
void PID_set_Pin_B(int S0, int S1, int S2, int S3, int S4, int S5, int S6, int S7) {
  PID_SetupPin_B[0] = S0;
  PID_SetupPin_B[1] = S1;
  PID_SetupPin_B[2] = S2;
  PID_SetupPin_B[3] = S3;
  PID_SetupPin_B[4] = S4;
  PID_SetupPin_B[5] = S5;
  PID_SetupPin_B[6] = S6;
  PID_SetupPin_B[7] = S7;
}
int readline_B() {
  bool onLine_B = false;
  long avg_B = 0;
  long sum_B = 0;
  for (uint8_t i = 0; i < PID_NumPin_B; i++) {
    long value_B;
    if (Black_color == 0) {
      value_B = map(ADC(PID_SetupPin_B[i]), PID_Min_B[i], PID_Max_B[i], 100, 0);
    } else {
      value_B = map(ADC(PID_SetupPin_B[i]), PID_Min_B[i], PID_Max_B[i], 0, 100);
    }
    value_B = constrain(value_B, 0, 100);
    if (value_B > Black_sensitive) {
      onLine_B = true;
    }
    if (value_B > 5) {
      avg_B += (long)value_B * (i * 100);
      sum_B += value_B;
    }
  }
  if (!onLine_B) {
    if (_lastPosition_B < ((PID_NumPin_B - 1) * 100) / 2) {
      return 0;
    } else {
      return ((PID_NumPin_B - 1) * 100);
    }
  }
  _lastPosition_B = avg_B / sum_B;
  return _lastPosition_B;
}
void Run_PID_B(int RUN_PID_speed, float RUN_PID_KP, float RUN_PID_KD) {
  int present_position_B = readline_B();
  int setpoint_B = ((PID_NumPin_B - 1) * 100) / 2;
  errors_B = present_position_B - setpoint_B;
  integral_B = integral_B + errors_B;
  derivative_B = (errors_B - previous_error_B);
  output_B = RUN_PID_KP * errors_B + RUN_PID_KD * derivative_B;

  int m1Speed = RUN_PID_speed - output_B;
  int m2Speed = RUN_PID_speed + output_B;

  motor(1, -m1Speed);
  motor(2, -m2Speed);
  delay(1);
  previous_error_B = errors_B;
}
long readDistance(int Trig, int Echo) {
  long duration, cm;
  pinMode(Echo, OUTPUT);
  digitalWrite(Echo, 0);
  delayMicroseconds(2);
  digitalWrite(Echo, 1);
  delayMicroseconds(5);
  digitalWrite(Echo, 0);
  pinMode(Trig, INPUT);
  duration = pulseIn(Trig, 1);
  return duration / 29 / 2;
}
bool Read_status_sensor(int pin_sensor) {
  return ADC(PID_SetupPin[pin_sensor]) < ((PID_Max[pin_sensor] + PID_Min[pin_sensor]) / 2) ? true : false;
}
bool Read_status_sensor_B(int pin_sensor) {
  return ADC(PID_SetupPin_B[pin_sensor]) < ((PID_Max_B[pin_sensor] + PID_Min_B[pin_sensor]) / 2) ? true : false;
}
void setCalibrate_B(int round) {
  //display.clear();
  //display.setFont(ArialMT_Plain_24);
  //display.drawString(0,0,"Black Sensor");
  //display.drawString(0,25,"  Calribrate  ");
  //display.//display();
  if (first_state_for_calribrate_B == 0) {
    for (uint8_t i = 0; i < PID_NumPin_B; i++) {
      PID_Max_B[i] = 0;
      PID_Min_B[i] = 4095;
    }
    first_state_for_calribrate_B = 1;
  }
  for (int roundOfCalribtate = 0; roundOfCalribtate < round; roundOfCalribtate++) {
    for (uint8_t i = 0; i < PID_NumPin_B; i++) {
      if (ADC(PID_SetupPin_B[i]) > PID_Max_B[i] || PID_Max_B[i] >= 4095) {
        PID_Max_B[i] = ADC(PID_SetupPin_B[i]);
        if (PID_Max_B[i] > 4095) PID_Max_B[i] = 4095;
      }
    }
    for (uint8_t i = 0; i < PID_NumPin_B; i++) {
      if (ADC(PID_SetupPin_B[i]) < PID_Min_B[i] || PID_Min_B[i] == 0) {
        PID_Min_B[i] = ADC(PID_SetupPin_B[i]);
        if (PID_Min_B[i] < 0) PID_Min_B[i] = 0;
      }
    }
    delay(1);
  }
  //display.clear();
}

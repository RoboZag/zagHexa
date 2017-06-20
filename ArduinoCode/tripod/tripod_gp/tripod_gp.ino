#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Ultrasonic.h>

#define SERVOMIN  150
#define SERVOMAX  550
#define newRx 11
#define newTx 12

#define RightFrontRot    0
#define RightFrontLift   1
#define RightFrontTibia  2
#define RightMiddleRot   3
#define RightMiddleLift  4
#define RightMiddleTibia 5
#define RightRearRot     6
#define RightRearLift    7
#define RightRearTibia   8
#define LeftFrontRot     9
#define LeftFrontLift    10
#define LeftFrontTibia   11
#define LeftMiddleRot    12
#define LeftMiddleLift   13
#define LeftMiddleTibia  14
#define LeftRearRot      15
#define LeftRearLift     16
#define LeftRearTibia    17

Adafruit_PWMServoDriver pwm  = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);

SoftwareSerial bluetooth(newRx, newTx);
Distance ultrasonic(7, 8); // 7 for echo pin and 8 for trigger pin

char data;
int mode = 1; //mode 1 for translation, mode 2 for tending, mode 3 for up and down
int refAngle[18];
int oldAngle[18];
int newAngle[18];
int distance;

void set_refAngle();
void init_oldAngle();
void reset_angles();
void calibrate();
int angle2pwm(int);
void twitch(int servo_num, int angle, int duration = 200);
void sitdown();
void standup();
void tripod_forward(int z_offset = 30, int y_offset = 15, int moveDelay = 100, int stepDelay = 70);
void tripod_backward(int z_offset = 30, int y_offset = 15, int moveDelay = 100, int stepDelay = 70);
void tripod_right(int z_offset = 30, int y_offset = 15, int moveDelay = 100, int stepDelay = 70);
void tripod_left(int z_offset = 30, int y_offset = 15, int moveDelay = 100, int stepDelay = 70);
void tilt_left();
void tilt_right();
void tilt_forward();
void tilt_backward();
long map_val(long, long, long, long, long);

void setup(){
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);
  pwm1.begin();
  pwm1.setPWMFreq(60);
  bluetooth.begin(9600);
  calibrate();
}

void loop(){   
  distance = ultrasonic.getdistance();
  if(bluetooth.available() > 0){
    data = bluetooth.read();
  }
  if(data == '1'){
    if(mode == 1){
      tripod_forward();
    }
    if(mode == 2){
      tilt_forward();
    }
    if(mode == 3){
      standup();
    }
  }
  if(data == '2'){
    if(mode == 1){
      tripod_left();
    }
    if(mode == 2){
      tilt_left();
    }
    if(mode == 3){
      
    }
  }
  if(data == '3'){
    if(mode == 1){
      tripod_backward();
    }
    if(mode == 2){
      tilt_backward();
    }
    if(mode == 3){
      sitdown();
    }
  }
  if(data == '4'){
    if(mode == 1){
      tripod_right();
    }
    if(mode == 2){
      tilt_right();
    }
    if(mode == 3){
      
    }
  }
  if(data == 'x'){
        
  }
  if(data == 't'){
    
  }  
  if(data == 'c'){
    mode++;
  }
  if(data == 's'){
    reset_angles();
  }
  if(mode > 3){
    mode = 1;
  }
}

void set_refAngle(){
  refAngle[RightFrontRot]    = 90;
  refAngle[RightFrontLift]   = 95;
  refAngle[RightFrontTibia]  = 92;
  refAngle[RightMiddleRot]   = 90;
  refAngle[RightMiddleLift]  = 93;
  refAngle[RightMiddleTibia] = 98;
  refAngle[RightRearRot]     = 90;
  refAngle[RightRearLift]    = 88;
  refAngle[RightRearTibia]   = 98;
  refAngle[LeftFrontRot]     = 90;
  refAngle[LeftFrontLift]    = 84;
  refAngle[LeftFrontTibia]   = 98;
  refAngle[LeftMiddleRot]    = 90;
  refAngle[LeftMiddleLift]   = 90;
  refAngle[LeftMiddleTibia]  = 98;
  refAngle[LeftRearRot]      = 90;
  refAngle[LeftRearLift]     = 83;
  refAngle[LeftRearTibia]    = 95;  
 }

void init_oldAngle(){
  for(int i = 0; i < 18; i++){
    oldAngle[i] = refAngle[i];
  }
}

void reset_angles(){
  for(int servo_num = 0; servo_num <= 17; servo_num++){
    if(servo_num >= 0 && servo_num <= 8){
      pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num]));              
    }
    else{
      pwm1.setPWM((servo_num - 9), 0, angle2pwm(refAngle[servo_num]));
    }
  }
}

void calibrate(){
  set_refAngle();
  init_oldAngle();
  reset_angles();
  delay(2000);
  }

long map_val(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int angle2pwm(int angle){
  int pulse_len = map_val(angle, 0, 180, SERVOMIN, SERVOMAX);
  return pulse_len;
}

void twitch(int servo_num, int angle, int duration = 200){
  if(servo_num >= 0 && servo_num <= 8){
    newAngle[servo_num] = refAngle[servo_num] - angle;
    if(newAngle[servo_num] >= oldAngle[servo_num]){
      for(int i = oldAngle[servo_num]; i <= newAngle[servo_num]; i++){
        pwm.setPWM(servo_num, 0, angle2pwm(i));
        delayMicroseconds(duration);    
      }
    }
    else{
      for(int i = oldAngle[servo_num]; i >= newAngle[servo_num]; i--){
        pwm.setPWM(servo_num, 0, angle2pwm(i));
        delayMicroseconds(duration);    
      }
    }  
  }
  else if(servo_num >= 9 && servo_num <= 17){
    newAngle[servo_num] = refAngle[servo_num] + angle;
    if(newAngle[servo_num] >= oldAngle[servo_num]){
      for(int i = oldAngle[servo_num]; i <= newAngle[servo_num]; i++){
        pwm1.setPWM((servo_num - 9), 0, angle2pwm(i));
        delayMicroseconds(duration);    
      }
    }
    else{
      for(int i = oldAngle[servo_num]; i >= newAngle[servo_num]; i--){
        pwm1.setPWM((servo_num - 9), 0, angle2pwm(i));
        delayMicroseconds(duration);    
      }
    }  
  }
  oldAngle[servo_num] = newAngle[servo_num];
}

void sitdown(){
  for(int servo_num = 0; servo_num < 18; servo_num++){
    if(servo_num >= 0 && servo_num <= 8){
      if((servo_num % 3) == 0){
       pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num])); 
      }
      else{
       pwm.setPWM(servo_num, 0, angle2pwm((refAngle[servo_num] - 30))); 
      }
    }
    if(servo_num >= 9 && servo_num <= 17){
      if((servo_num % 3) == 0){
       pwm1.setPWM((servo_num - 9), 0, angle2pwm(refAngle[servo_num]));         
      }
      else{
       pwm1.setPWM((servo_num - 9), 0, angle2pwm((refAngle[servo_num] + 30)));       
      }
    }
  }
}

void standup(){
  for(int servo_num = 0; servo_num < 18; servo_num++){
    if(servo_num >= 0 && servo_num <= 8){
      if((servo_num % 3) == 0){
       pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num])); 
      }
      else{
       pwm.setPWM(servo_num, 0, angle2pwm((refAngle[servo_num] + 30))); 
      }
    }
    if(servo_num >= 9 && servo_num <= 17){
      if((servo_num % 3) == 0){
       pwm1.setPWM((servo_num - 9), 0, angle2pwm(refAngle[servo_num]));         
      }
      else{
       pwm1.setPWM((servo_num - 9), 0, angle2pwm((refAngle[servo_num] - 30)));       
      }
    }
  }
}

void tilt_forward(){
  for(int servo_num = 0; servo_num < 18; servo_num++){
    if(servo_num >= 0 && servo_num <= 8){
      if((servo_num % 3) == 0){
       pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num] + 20)); 
      }
    }
    if(servo_num >= 9 && servo_num <= 17){
      if((servo_num % 3) == 0){
       pwm1.setPWM((servo_num - 9), 0, angle2pwm(refAngle[servo_num] - 20));         
      }
    }
  }
}

void tilt_backward(){
  for(int servo_num = 0; servo_num < 18; servo_num++){
    if(servo_num >= 0 && servo_num <= 8){
      if((servo_num % 3) == 0){
       pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num] - 20)); 
      }
    }
    if(servo_num >= 9 && servo_num <= 17){
      if((servo_num % 3) == 0){
       pwm1.setPWM((servo_num - 9), 0, angle2pwm(refAngle[servo_num] + 20));         
      }
    }
  }
}

void tilt_right(){
  for(int servo_num = 0; servo_num < 18; servo_num++){
    if(servo_num >= 0 && servo_num <= 8){
      if((servo_num % 3) == 0){
       pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num] - 20)); 
      }
    }
    if(servo_num >= 9 && servo_num <= 17){
      if((servo_num % 3) == 0){
       pwm1.setPWM((servo_num - 9), 0, angle2pwm(refAngle[servo_num] - 20));         
      }
    }
  }
}

void tilt_left(){
  for(int servo_num = 0; servo_num < 18; servo_num++){
    if(servo_num >= 0 && servo_num <= 8){
      if((servo_num % 3) == 0){
       pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num] + 20)); 
      }
    }
    if(servo_num >= 9 && servo_num <= 17){
      if((servo_num % 3) == 0){
       pwm1.setPWM((servo_num - 9), 0, angle2pwm(refAngle[servo_num] + 20));         
      }
    }
  }
}

void shrink(){
  for(int servo_num = 0; servo_num < 18; servo_num++){
    if(servo_num >= 0 && servo_num <= 8){
      if((servo_num % 3) == 0){
       pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num])); 
      }
      else{
       pwm.setPWM(servo_num, 0, angle2pwm((refAngle[servo_num] - 70))); 
      }
    }
    if(servo_num >= 9 && servo_num <= 17){
      if((servo_num % 3) == 0){
       pwm1.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num]));         
      }
      else{
       pwm1.setPWM(servo_num, 0, angle2pwm((refAngle[servo_num] + 70)));       
      }
    }
  }  
}

void tripod_forward(int z_offset = 30, int y_offset = 15, int moveDelay = 100, int stepDelay = 70){  
  twitch(RightFrontLift,   z_offset,  moveDelay);   //raise right front leg 
  twitch(RightRearLift,    z_offset,  moveDelay);   //raise right rear leg
  twitch(LeftMiddleLift,   z_offset,  moveDelay);   //raise left middle leg
  delay(stepDelay);
  twitch(RightFrontRot,    y_offset,  moveDelay);   //move right front leg forward
  twitch(RightRearRot,     y_offset,  moveDelay);   //move right rear leg forward
  twitch(LeftMiddleRot,    y_offset,  moveDelay);   //move left middle leg forward
  twitch(LeftFrontRot,   -(y_offset), moveDelay);   //move left front leg backward
  twitch(LeftRearRot,    -(y_offset), moveDelay);   //move left rear leg backward
  twitch(RightMiddleRot, -(y_offset), moveDelay);   //move right middle leg backward
  delay(stepDelay);
  twitch(RightFrontLift,   0,         moveDelay);   //lower right front leg
  twitch(RightFrontTibia,  0,         moveDelay);   //fix right front Tibia
  twitch(RightRearLift,    0,         moveDelay);   //lower right rear leg
  twitch(RightRearTibia,   0,         moveDelay);   //fix right rear Tibia
  twitch(LeftMiddleLift,   0,         moveDelay);   //lower left middle leg
  twitch(LeftMiddleTibia,  0,         moveDelay);   //fix left middle Tibia  
  delay(stepDelay);
  twitch(LeftFrontLift,    z_offset,  moveDelay);   //raise left front leg 
  twitch(LeftRearLift,     z_offset,  moveDelay);   //raise left rear leg
  twitch(RightMiddleLift,  z_offset,  moveDelay);   //raise Right middle leg
  delay(stepDelay);
  twitch(LeftFrontRot,     y_offset,  moveDelay);   //move left front leg forward
  twitch(LeftRearRot,      y_offset,  moveDelay);   //move left rear leg forward
  twitch(RightMiddleRot,   y_offset,  moveDelay);   //move right middle leg forward
  twitch(RightFrontRot,  -(y_offset), moveDelay);   //move right front leg backward
  twitch(RightRearRot,   -(y_offset), moveDelay);   //move right rear leg backward
  twitch(LeftMiddleRot,  -(y_offset), moveDelay);   //move left middle leg backward
  delay(stepDelay); 
  twitch(LeftFrontLift,    0,         moveDelay);   //lower left front leg
  twitch(LeftFrontTibia,   0,         moveDelay);   //fix left front Tibia
  twitch(LeftRearLift,     0,         moveDelay);   //lower left rear leg
  twitch(LeftRearTibia,    0,         moveDelay);   //fix left rear Tibia
  twitch(RightMiddleLift,  0,         moveDelay);   //lower right middle leg
  twitch(RightMiddleTibia, 0,         moveDelay);   //fix right middle Tibia
  delay(stepDelay);
}

void tripod_backward(int z_offset = 30, int y_offset = 15, int moveDelay = 100, int stepDelay = 70){  
  twitch(LeftRearLift,     z_offset,  moveDelay);  //raise right front leg 
  twitch(LeftFrontLift,    z_offset,  moveDelay);  //raise right rear leg
  twitch(RightMiddleLift,  z_offset,  moveDelay);  //raise left middle leg
  delay(stepDelay);
  twitch(LeftRearRot,    -(y_offset), moveDelay);  //move right front leg forward
  twitch(LeftFrontRot,   -(y_offset), moveDelay);  //move right rear leg forward
  twitch(RightMiddleRot, -(y_offset), moveDelay);  //move left middle leg forward
  twitch(RightRearRot,     y_offset,  moveDelay);  //move left front leg backward
  twitch(RightFrontRot,    y_offset,  moveDelay);  //move left rear leg backward
  twitch(LeftMiddleRot,    y_offset,  moveDelay);  //move right middle leg backward
  delay(stepDelay);
  twitch(LeftRearLift,     0,         moveDelay);  //lower right front leg
  twitch(LeftRearTibia,    0,         moveDelay);  //fix right front Tibia
  twitch(LeftFrontLift,    0,         moveDelay);  //lower right rear leg
  twitch(LeftFrontTibia,   0,         moveDelay);  //fix right rear Tibia
  twitch(RightMiddleLift,  0,         moveDelay);  //lower left middle leg
  twitch(RightMiddleTibia, 0,         moveDelay);  //fix left middle Tibia  
  delay(stepDelay);
  twitch(RightRearLift,    z_offset,  moveDelay);  //raise left front leg 
  twitch(RightFrontLift,   z_offset,  moveDelay);  //raise left rear leg
  twitch(LeftMiddleLift,   z_offset,  moveDelay);  //raise Right middle leg
  delay(stepDelay);
  twitch(RightRearRot,   -(y_offset), moveDelay);  //move left front leg forward
  twitch(RightFrontRot,  -(y_offset), moveDelay);  //move left rear leg forward
  twitch(LeftMiddleRot,  -(y_offset), moveDelay);  //move right middle leg forward
  twitch(LeftRearRot,      y_offset,  moveDelay);  //move right front leg backward
  twitch(LeftFrontRot,     y_offset,  moveDelay);  //move right rear leg backward
  twitch(RightMiddleRot,   y_offset,  moveDelay);  //move left middle leg backward
  delay(stepDelay); 
  twitch(RightRearLift,    0,         moveDelay);  //lower left front leg
  twitch(RightRearTibia,   0,         moveDelay);  //fix left front Tibia
  twitch(RightFrontLift,   0,         moveDelay);  //lower left rear leg
  twitch(RightFrontTibia,  0,         moveDelay);  //fix left rear Tibia
  twitch(LeftMiddleLift,   0,         moveDelay);  //lower right middle leg
  twitch(LeftMiddleTibia,  0,         moveDelay);  //fix right middle Tibia
  delay(stepDelay);
}

void tripod_left(int z_offset = 30, int y_offset = 15, int moveDelay = 100, int stepDelay = 70){  
  twitch(RightFrontLift,     z_offset,  moveDelay);  //raise right front leg 
  twitch(RightRearLift,    z_offset,  moveDelay);  //raise right rear leg
  twitch(LeftMiddleLift,  z_offset,  moveDelay);  //raise left middle leg
  delay(stepDelay);
  twitch(RightFrontRot,    y_offset, moveDelay);  //move right front leg forward
  twitch(RightRearRot,   y_offset, moveDelay);  //move right rear leg forward
  twitch(LeftMiddleRot, -(y_offset), moveDelay);  //move left middle leg forward
  twitch(LeftFrontRot,     y_offset,  moveDelay);  //move left front leg backward
  twitch(LeftRearRot,    y_offset,  moveDelay);  //move left rear leg backward
  twitch(RightMiddleRot,    -(y_offset),  moveDelay);  //move right middle leg backward
  delay(stepDelay);
  twitch(RightFrontLift,     0,         moveDelay);  //lower right front leg
  twitch(RightRearTibia,    0,         moveDelay);  //fix right front Tibia
  twitch(LeftMiddleLift,    0,         moveDelay);  //lower right rear leg
  twitch(RightFrontTibia,   0,         moveDelay);  //fix right rear Tibia
  twitch(RightRearLift,  0,         moveDelay);  //lower left middle leg
  twitch(LeftMiddleTibia, 0,         moveDelay);  //fix left middle Tibia  
  delay(stepDelay);
  twitch(LeftFrontLift,    z_offset,  moveDelay);  //raise left front leg 
  twitch(LeftRearLift,   z_offset,  moveDelay);  //raise left rear leg
  twitch(RightMiddleLift,   z_offset,  moveDelay);  //raise Right middle leg
  delay(stepDelay);
  twitch(LeftFrontRot,   -(y_offset), moveDelay);  //move left front leg forward
  twitch(LeftRearRot,  -(y_offset), moveDelay);  //move left rear leg forward
  twitch(RightMiddleRot,  y_offset, moveDelay);  //move right middle leg forward
  twitch(RightFrontRot,      -(y_offset),  moveDelay);  //move right front leg backward
  twitch(RightRearRot,     -(y_offset),  moveDelay);  //move right rear leg backward
  twitch(LeftMiddleRot,   y_offset,  moveDelay);  //move left middle leg backward
  delay(stepDelay); 
  twitch(LeftFrontLift,    0,         moveDelay);  //lower left front leg
  twitch(LeftRearLift,   0,         moveDelay);  //fix left front Tibia
  twitch(RightMiddleLift,   0,         moveDelay);  //lower left rear leg
  twitch(LeftFrontTibia,  0,         moveDelay);  //fix left rear Tibia
  twitch(LeftRearTibia,   0,         moveDelay);  //lower right middle leg
  twitch(RightMiddleTibia,  0,         moveDelay);  //fix right middle Tibia
  delay(stepDelay);
}

void tripod_right(int z_offset = 30, int y_offset = 15, int moveDelay = 100, int stepDelay = 70){  
  twitch(LeftFrontLift,     z_offset,  moveDelay);  //raise left front leg 
  twitch(LeftRearLift,      z_offset,  moveDelay);  //raise left rear leg
  twitch(RightMiddleLift,   z_offset,  moveDelay);  //raise right middle leg
  delay(stepDelay);
  twitch(LeftFrontRot,      y_offset,  moveDelay);  //move left front leg forward
  twitch(LeftRearRot,       y_offset,  moveDelay);  //move left rear leg forward
  twitch(RightMiddleRot,  -(y_offset), moveDelay);  //move right middle leg backward
  twitch(RightFrontRot,     y_offset,  moveDelay);  //move right front leg forward
  twitch(RightRearRot,      y_offset,  moveDelay);  //move right rear leg forward
  twitch(LeftMiddleRot,   -(y_offset), moveDelay);  //move left middle leg backward
  delay(stepDelay);
  twitch(LeftFrontLift,     0,         moveDelay);  //lower left front leg
  twitch(LeftRearLift,      0,         moveDelay);  //lower left rear leg
  twitch(RightMiddleLift,   0,         moveDelay);  //lower right middle leg
  twitch(LeftFrontTibia,    0,         moveDelay);  //fix left front Tibia
  twitch(LeftRearTibia,     0,         moveDelay);  //fix left rear Tibia
  twitch(RightMiddleTibia,  0,         moveDelay);  //fix right middle Tibia  
  delay(stepDelay);
  twitch(RightFrontLift,    z_offset,  moveDelay);  //raise right front leg 
  twitch(RightRearLift,     z_offset,  moveDelay);  //raise right rear leg
  twitch(LeftMiddleLift,    z_offset,  moveDelay);  //raise left middle leg
  delay(stepDelay);
  twitch(RightFrontRot,   -(y_offset), moveDelay);  //move right front leg backward
  twitch(RightRearRot,    -(y_offset), moveDelay);  //move right rear leg backward
  twitch(LeftMiddleRot,     y_offset,  moveDelay);  //move left middle leg forward
  twitch(LeftFrontRot,    -(y_offset), moveDelay);  //move left front leg backward
  twitch(LeftRearRot,     -(y_offset), moveDelay);  //move left rear leg backward
  twitch(RightMiddleRot,    y_offset,  moveDelay);  //move right middle leg forward
  delay(stepDelay); 
  twitch(RightFrontLift,    0,         moveDelay);  //lower right front leg
  twitch(RightRearLift,     0,         moveDelay);  //lower right rear leg
  twitch(LeftMiddleLift,    0,         moveDelay);  //lower left middle leg
  twitch(RightFrontTibia,   0,         moveDelay);  //fix right front Tibia
  twitch(RightRearTibia,    0,         moveDelay);  //fix right rear Tibia
  twitch(LeftMiddleTibia,   0,         moveDelay);  //fix right middle Tibia
  delay(stepDelay);
}

#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

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

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
SoftwareSerial bluetooth(newRx, newTx);
Servo myservo1 ;
Servo myservo2 ;

char data;
int refAngle[18];
int oldAngle[18];
int newAngle[18];

void set_refAngle(){
  refAngle[RightFrontRot]    = 90;
  refAngle[RightFrontLift]   = 90;
  refAngle[RightFrontTibia]  = 90;
  refAngle[RightMiddleRot]   = 90;
  refAngle[RightMiddleLift]  = 90;
  refAngle[RightMiddleTibia] = 90;
  refAngle[RightRearRot]     = 90;
  refAngle[RightRearLift]    = 90;
  refAngle[RightRearTibia]   = 90;
  refAngle[LeftFrontRot]     = 90;
  refAngle[LeftFrontLift]    = 90;
  refAngle[LeftFrontTibia]   = 90;
  refAngle[LeftMiddleRot]    = 90;
  refAngle[LeftMiddleLift]   = 90;
  refAngle[LeftMiddleTibia]  = 90;
  refAngle[LeftRearRot]      = 90;
  refAngle[LeftRearLift]     = 90;
  refAngle[LeftRearTibia]    = 90;  
 }

void init_oldAngle(){
  for(int i = 0; i < 18; i++){
    oldAngle[i] = refAngle[i];
  }
}

void reset_angles(){
  for(int servo_num = 0; servo_num < 16; servo_num++){
    pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num]));        
  }
  myservo1.write(refAngle[16]);
  myservo2.write(refAngle[17]);
}

void calibrate(){
  set_refAngle();
  init_oldAngle();
  reset_angles();
  delay(2000);
  }

int angle2pwm(int angle){
  int pulse_len = map(angle, 0, 180, SERVOMIN, SERVOMAX);
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
  else if(servo_num >= 9 && servo_num <= 15){
    newAngle[servo_num] = refAngle[servo_num] + angle;
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
  else if(servo_num == 16){
    newAngle[servo_num] = refAngle[servo_num] + angle;
    if(newAngle[servo_num] >= oldAngle[servo_num]){
      for(int i = oldAngle[servo_num]; i <= newAngle[servo_num]; i++){
        myservo1.write(i);
        delayMicroseconds(duration);    
      }
    }
    else{
      for(int i = oldAngle[servo_num]; i >= newAngle[servo_num]; i--){
        myservo1.write(i);
        delayMicroseconds(duration);    
      }
    }  
  }
  else if(servo_num == 17){
    newAngle[servo_num] = refAngle[servo_num] + angle;
    if(newAngle[servo_num] >= oldAngle[servo_num]){
      for(int i = oldAngle[servo_num]; i <= newAngle[servo_num]; i++){
        myservo2.write(i);
        delayMicroseconds(duration);    
      }
    }
    else{
      for(int i = oldAngle[servo_num]; i >= newAngle[servo_num]; i--){
        myservo2.write(i);
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
    if(servo_num >= 9 && servo_num <= 15){
      if((servo_num % 3) == 0){
       pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num]));         
      }
      else{
       pwm.setPWM(servo_num, 0, angle2pwm((refAngle[servo_num] + 30)));       
      }
    }
    if(servo_num == 16){
      myservo1.write((refAngle[servo_num] + 30));
    }
    if(servo_num == 17){
      myservo2.write((refAngle[servo_num] + 30));
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
    if(servo_num >= 9 && servo_num <= 15){
      if((servo_num % 3) == 0){
       pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num]));         
      }
      else{
       pwm.setPWM(servo_num, 0, angle2pwm((refAngle[servo_num] - 30)));       
      }
    }
    if(servo_num == 16){
      myservo1.write((refAngle[servo_num] - 30));
    }
    if(servo_num == 17){
      myservo2.write((refAngle[servo_num] - 30));
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
    if(servo_num >= 9 && servo_num <= 15){
      if((servo_num % 3) == 0){
       pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num]));         
      }
      else{
       pwm.setPWM(servo_num, 0, angle2pwm((refAngle[servo_num] + 70)));       
      }
    }
    if(servo_num == 16){
      myservo1.write((refAngle[servo_num] + 70));
    }
    if(servo_num == 17){
      myservo2.write((refAngle[servo_num] + 70));
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
  twitch(LeftFrontLift,     z_offset,  moveDelay);  //raise right front leg 
  twitch(LeftRearLift,    z_offset,  moveDelay);  //raise right rear leg
  twitch(RightMiddleLift,  z_offset,  moveDelay);  //raise left middle leg
  delay(stepDelay);
  twitch(LeftFrontRot,    y_offset, moveDelay);  //move right front leg forward
  twitch(LeftRearRot,   y_offset, moveDelay);  //move right rear leg forward
  twitch(RightMiddleRot, -(y_offset), moveDelay);  //move left middle leg forward
  twitch(RightFrontRot,     y_offset,  moveDelay);  //move left front leg backward
  twitch(RightRearRot,    y_offset,  moveDelay);  //move left rear leg backward
  twitch(LeftMiddleRot,    -(y_offset),  moveDelay);  //move right middle leg backward
  delay(stepDelay);
  twitch(LeftFrontLift,     0,         moveDelay);  //lower right front leg
  twitch(LeftRearLift,    0,         moveDelay);  //fix right front Tibia
  twitch(RightMiddleLift,    0,         moveDelay);  //lower right rear leg
  twitch(LeftFrontTibia,   0,         moveDelay);  //fix right rear Tibia
  twitch(LeftRearTibia,  0,         moveDelay);  //lower left middle leg
  twitch(RightMiddleTibia, 0,         moveDelay);  //fix left middle Tibia  
  delay(stepDelay);
  twitch(RightFrontLift,    z_offset,  moveDelay);  //raise left front leg 
  twitch(RightRearLift,   z_offset,  moveDelay);  //raise left rear leg
  twitch(LeftMiddleLift,   z_offset,  moveDelay);  //raise Right middle leg
  delay(stepDelay);
  twitch(RightFrontRot,   -(y_offset), moveDelay);  //move left front leg forward
  twitch(RightRearRot,  -(y_offset), moveDelay);  //move left rear leg forward
  twitch(LeftMiddleRot,  y_offset, moveDelay);  //move right middle leg forward
  twitch(LeftFrontRot,      -(y_offset),  moveDelay);  //move right front leg backward
  twitch(LeftRearRot,     -(y_offset),  moveDelay);  //move right rear leg backward
  twitch(RightMiddleRot,   y_offset,  moveDelay);  //move left middle leg backward
  delay(stepDelay); 
  twitch(RightFrontLift,    0,         moveDelay);  //lower left front leg
  twitch(RightRearLift,   0,         moveDelay);  //fix left front Tibia
  twitch(LeftMiddleLift,   0,         moveDelay);  //lower left rear leg
  twitch(RightFrontTibia,  0,         moveDelay);  //fix left rear Tibia
  twitch(RightRearTibia,   0,         moveDelay);  //lower right middle leg
  twitch(LeftMiddleTibia,  0,         moveDelay);  //fix right middle Tibia
  delay(stepDelay);
}

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);
  myservo1.attach(9);
  myservo2.attach(10);
  bluetooth.begin(9600);
  calibrate();
}

void loop() {   
  if(bluetooth.available() > 0){
    data = bluetooth.read();
  }
  if(data == 'A'){
    tripod_forward();
  }
  if(data == 'B'){
    tripod_backward();
  }
  if(data == 'D'){
    tripod_right();
  }
  if(data == 'C'){
    tripod_left();
  } 
  if(data == 'I'){
    standup();
  }
  if(data == 'J'){
    sitdown();
  }
  if(data == 'K'){
    reset_angles();
  }
}

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
int mode = 1; //mode 1 for translation, mode 2 for tending, mode 3 for up and down
int refAngle[18];
int oldAngle[18];
int newAngle[18];

int z_offset = 30; //min 20 max 35 step 5       (speed list:  20   25   30   35)
int y_offset = 15; //min 5 max 20 step 5        (speed list:  5    10   15   20)
int microDelay = 100; //min 200 max 50 step 50  (speed list:  200  150  100  50)
int milliDelay = 70; //min 160 max 70 step 30  (speed list:  160  130  100  70)

void set_refAngle();
void init_oldAngle();
void reset_angles();
void calibrate();
int angle2pwm(int);
void twitch(int servo_num, int angle, int duration = 200);
void sitdown();
void standup();
void tripod_forward(int z_offset, int y_offset, int moveDelay, int stepDelay);
void tripod_backward(int z_offset, int y_offset, int moveDelay, int stepDelay);
void tripod_right(int z_offset, int y_offset, int moveDelay, int stepDelay);
void tripod_left(int z_offset, int y_offset, int moveDelay, int stepDelay);
void tilt_left();
void tilt_right();
void tilt_forward();
void tilt_backward();

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);
  myservo1.attach(9);
  myservo2.attach(10);
  bluetooth.begin(9600);
  calibrate();
}

void loop(){   
  if(bluetooth.available() > 0){
    data = bluetooth.read();
  }
  if(data == 'A'){
    if(mode == 1){
      tripod_forward(z_offset, y_offset, microDelay, milliDelay);
    }
    if(mode == 2){
      tilt_forward();
    }
    if(mode == 3){
      standup();
    }
  }
  if(data == 'C'){
    if(mode == 1){
      tripod_left(z_offset, y_offset, microDelay, milliDelay);
    }
    if(mode == 2){
      tilt_left();
    }
    if(mode == 3){
      
    }
  }
  if(data == 'B'){
    if(mode == 1){
      tripod_backward(z_offset, y_offset, microDelay, milliDelay);
    }
    if(mode == 2){
      tilt_backward();
    }
    if(mode == 3){
      sitdown();
    }
  }
  if(data == 'D'){
    if(mode == 1){
      tripod_right(z_offset, y_offset, microDelay, milliDelay);
    }
    if(mode == 2){
      tilt_right();
    }
    if(mode == 3){
      
    }
  }
  if(data == 'L'){
        
  }
  if(data == 'I'){
    
  }
  if(data == 'G'){
    mode++;
  }
  if(data == 'N'){
    z_offset -= 5;
    y_offset -= 5;
    microDelay += 50;
    milliDelay += 30;
  }
  if(data == 'F'){
    z_offset += 5;
    y_offset += 5;
    microDelay -= 50;
    milliDelay -= 30;
  }
  if(data == 'K'){
    reset_angles();
  }
  if(mode > 3){
    mode = 1;
  }
/*  if(z_offset > 35){
    z_offset = ;
    y_offset = ;
    microDelay = ;
    milliDelay = ;    
  }
  else if(z_offset < 15){
    z_offset = 10;
    y_offset = ;
    microDelay = ;
    milliDelay = ;    
  }

/*pwm.setPWM(0, 0, angle2pwm(85));
pwm.setPWM(1, 0, angle2pwm(105));
pwm.setPWM(2, 0, angle2pwm(95));
pwm.setPWM(3, 0, angle2pwm(90));
pwm.setPWM(4, 0, angle2pwm(98));
pwm.setPWM(5, 0, angle2pwm(94));
pwm.setPWM(6, 0, angle2pwm(85));
pwm.setPWM(7, 0, angle2pwm(90));
pwm.setPWM(8, 0, angle2pwm(99));
pwm.setPWM(9, 0, angle2pwm(90));
pwm.setPWM(10, 0, angle2pwm(92));
pwm.setPWM(11, 0, angle2pwm(90));
pwm.setPWM(12, 0, angle2pwm(90));
pwm.setPWM(13, 0, angle2pwm(93));
pwm.setPWM(14, 0, angle2pwm(90));
pwm.setPWM(15, 0, angle2pwm(95));
myservo1.write(93);
myservo2.write(87);
*/

}

void set_refAngle(){
  refAngle[RightFrontRot]    = 85;
  refAngle[RightFrontLift]   = 105;
  refAngle[RightFrontTibia]  = 95;
  refAngle[RightMiddleRot]   = 90;
  refAngle[RightMiddleLift]  = 98;
  refAngle[RightMiddleTibia] = 94;
  refAngle[RightRearRot]     = 85;
  refAngle[RightRearLift]    = 90;
  refAngle[RightRearTibia]   = 99;
  refAngle[LeftFrontRot]     = 90;
  refAngle[LeftFrontLift]    = 92;
  refAngle[LeftFrontTibia]   = 90;
  refAngle[LeftMiddleRot]    = 90;
  refAngle[LeftMiddleLift]   = 93;
  refAngle[LeftMiddleTibia]  = 90;
  refAngle[LeftRearRot]      = 95;
  refAngle[LeftRearLift]     = 93;
  refAngle[LeftRearTibia]    = 87;  
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

void tilt_forward(){
  for(int servo_num = 0; servo_num < 18; servo_num++){
    if(servo_num >= 0 && servo_num <= 8){
      if((servo_num % 3) == 0){
       pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num] + 20)); 
      }
    }
    if(servo_num >= 9 && servo_num <= 15){
      if((servo_num % 3) == 0){
       pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num] - 20));         
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
    if(servo_num >= 9 && servo_num <= 15){
      if((servo_num % 3) == 0){
       pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num] + 20));         
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
    if(servo_num >= 9 && servo_num <= 15){
      if((servo_num % 3) == 0){
       pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num] - 20));         
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
    if(servo_num >= 9 && servo_num <= 15){
      if((servo_num % 3) == 0){
       pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num] + 20));         
      }
    }
  }
}

void tripod_forward(int z_offset, int y_offset, int moveDelay, int stepDelay){  
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

void tripod_backward(int z_offset, int y_offset, int moveDelay, int stepDelay){  
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

void tripod_left(int z_offset, int y_offset, int moveDelay, int stepDelay){  
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
void tripod_right(int z_offset, int y_offset, int moveDelay, int stepDelay){  
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

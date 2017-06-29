#include <SoftwareSerial.h>
#include <VarSpeedServo.h> 
/*
  - Start communication with RP
  - Receive struct { char (mode) int (direction) }
  - move the robot as wanted
*/
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

SoftwareSerial bluetooth(newRx, newTx);
VarSpeedServo servo[18];

/*
typedef struct {
char Mode;
int direction;
}stru;
stru serial_comm_port;
*/

char data;  //Replace data with serial_comm_port->mode or serial_comm_port -> direction 

int refAngle[18];

void init_refAngle();
void attach_servo();
void init_servo();
void calibrate();
void twitch(int servo_num, int angle, int velocity);
void tripod_forward(int z_offset = 30, int y_offset = 15, int velocity = 100, int stepDelay = 70);
void tripod_backward(int z_offset = 30, int y_offset = 15, int velocity = 100, int stepDelay = 70);
void tripod_right(int z_offset = 30, int y_offset = 15, int velocity = 100, int stepDelay = 70);
void tripod_left(int z_offset = 30, int y_offset = 15, int velocity = 100, int stepDelay = 70);
long map_val(long, long, long, long, long);

void setup(){
  Serial.begin(9600);
  bluetooth.begin(9600);
  calibrate();
}

void loop(){   
  if(bluetooth.available() > 0){
    data = bluetooth.read();
  }
  if(data == '1'){
    tripod_forward();
  }
  if(data == '2'){
    tripod_left();
  }
  if(data == '3'){
    tripod_backward();
  }
  if(data == '4'){
    tripod_right();
  }
}

void init_refAngle(){
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
 
 void attach_servo(){
  for(int i = 0; i = 17; i++){
    servo[i].attach(i);
  }
}

 void init_servo(int velocity){
  for(int i = 0; i = 17; i++){
    servo[i].write(refAngle[i], velocity, false);
  }
}

void calibrate(){
  init_refAngle();
  attach_servo();
  init_servo(127);
  delay(2000);
  }

long map_val(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int correct_angle(int servo_num, int angle){
  if(servo_num >= 0 && servo_num <= 8){
    angle = refAngle[servo_num] - angle;
  }
  else if(servo_num >= 9 && servo_num <= 17){
    angle = refAngle[servo_num] + angle;
  }  
}

void twitch(int servo_num, int angle, int velocity){
  int new_angle = correct_angle(servo_num, angle);
  servo[servo_num].write(new_angle, velocity, false);
}

void tripod_forward(int z_offset = 30, int y_offset = 15, int velocity, int stepDelay = 70){  
  twitch(RightFrontLift,   z_offset,  velocity);   //raise right front leg 
  twitch(RightRearLift,    z_offset,  velocity);   //raise right rear leg
  twitch(LeftMiddleLift,   z_offset,  velocity);   //raise left middle leg
  delay(stepDelay);
  twitch(RightFrontRot,    y_offset,  velocity);   //move right front leg forward
  twitch(RightRearRot,     y_offset,  velocity);   //move right rear leg forward
  twitch(LeftMiddleRot,    y_offset,  velocity);   //move left middle leg forward
  twitch(LeftFrontRot,   -(y_offset), velocity);   //move left front leg backward
  twitch(LeftRearRot,    -(y_offset), velocity);   //move left rear leg backward
  twitch(RightMiddleRot, -(y_offset), velocity);   //move right middle leg backward
  delay(stepDelay);
  twitch(RightFrontLift,   0,         velocity);   //lower right front leg
  twitch(RightFrontTibia,  0,         velocity);   //fix right front Tibia
  twitch(RightRearLift,    0,         velocity);   //lower right rear leg
  twitch(RightRearTibia,   0,         velocity);   //fix right rear Tibia
  twitch(LeftMiddleLift,   0,         velocity);   //lower left middle leg
  twitch(LeftMiddleTibia,  0,         velocity);   //fix left middle Tibia  
  delay(stepDelay);
  twitch(LeftFrontLift,    z_offset,  velocity);   //raise left front leg 
  twitch(LeftRearLift,     z_offset,  velocity);   //raise left rear leg
  twitch(RightMiddleLift,  z_offset,  velocity);   //raise Right middle leg
  delay(stepDelay);
  twitch(LeftFrontRot,     y_offset,  velocity);   //move left front leg forward
  twitch(LeftRearRot,      y_offset,  velocity);   //move left rear leg forward
  twitch(RightMiddleRot,   y_offset,  velocity);   //move right middle leg forward
  twitch(RightFrontRot,  -(y_offset), velocity);   //move right front leg backward
  twitch(RightRearRot,   -(y_offset), velocity);   //move right rear leg backward
  twitch(LeftMiddleRot,  -(y_offset), velocity);   //move left middle leg backward
  delay(stepDelay); 
  twitch(LeftFrontLift,    0,         velocity);   //lower left front leg
  twitch(LeftFrontTibia,   0,         velocity);   //fix left front Tibia
  twitch(LeftRearLift,     0,         velocity);   //lower left rear leg
  twitch(LeftRearTibia,    0,         velocity);   //fix left rear Tibia
  twitch(RightMiddleLift,  0,         velocity);   //lower right middle leg
  twitch(RightMiddleTibia, 0,         velocity);   //fix right middle Tibia
  delay(stepDelay);
}

void tripod_backward(int z_offset = 30, int y_offset = 15, int velocity = 100, int stepDelay = 70){  
  twitch(LeftRearLift,     z_offset,  velocity);  //raise right front leg 
  twitch(LeftFrontLift,    z_offset,  velocity);  //raise right rear leg
  twitch(RightMiddleLift,  z_offset,  velocity);  //raise left middle leg
  delay(stepDelay);
  twitch(LeftRearRot,    -(y_offset), velocity);  //move right front leg forward
  twitch(LeftFrontRot,   -(y_offset), velocity);  //move right rear leg forward
  twitch(RightMiddleRot, -(y_offset), velocity);  //move left middle leg forward
  twitch(RightRearRot,     y_offset,  velocity);  //move left front leg backward
  twitch(RightFrontRot,    y_offset,  velocity);  //move left rear leg backward
  twitch(LeftMiddleRot,    y_offset,  velocity);  //move right middle leg backward
  delay(stepDelay);
  twitch(LeftRearLift,     0,         velocity);  //lower right front leg
  twitch(LeftRearTibia,    0,         velocity);  //fix right front Tibia
  twitch(LeftFrontLift,    0,         velocity);  //lower right rear leg
  twitch(LeftFrontTibia,   0,         velocity);  //fix right rear Tibia
  twitch(RightMiddleLift,  0,         velocity);  //lower left middle leg
  twitch(RightMiddleTibia, 0,         velocity);  //fix left middle Tibia  
  delay(stepDelay);
  twitch(RightRearLift,    z_offset,  velocity);  //raise left front leg 
  twitch(RightFrontLift,   z_offset,  velocity);  //raise left rear leg
  twitch(LeftMiddleLift,   z_offset,  velocity);  //raise Right middle leg
  delay(stepDelay);
  twitch(RightRearRot,   -(y_offset), velocity);  //move left front leg forward
  twitch(RightFrontRot,  -(y_offset), velocity);  //move left rear leg forward
  twitch(LeftMiddleRot,  -(y_offset), velocity);  //move right middle leg forward
  twitch(LeftRearRot,      y_offset,  velocity);  //move right front leg backward
  twitch(LeftFrontRot,     y_offset,  velocity);  //move right rear leg backward
  twitch(RightMiddleRot,   y_offset,  velocity);  //move left middle leg backward
  delay(stepDelay); 
  twitch(RightRearLift,    0,         velocity);  //lower left front leg
  twitch(RightRearTibia,   0,         velocity);  //fix left front Tibia
  twitch(RightFrontLift,   0,         velocity);  //lower left rear leg
  twitch(RightFrontTibia,  0,         velocity);  //fix left rear Tibia
  twitch(LeftMiddleLift,   0,         velocity);  //lower right middle leg
  twitch(LeftMiddleTibia,  0,         velocity);  //fix right middle Tibia
  delay(stepDelay);
}

void tripod_left(int z_offset = 30, int y_offset = 15, int velocity = 100, int stepDelay = 70){  
  twitch(RightFrontLift,     z_offset,  velocity);  //raise right front leg 
  twitch(RightRearLift,    z_offset,  velocity);  //raise right rear leg
  twitch(LeftMiddleLift,  z_offset,  velocity);  //raise left middle leg
  delay(stepDelay);
  twitch(RightFrontRot,    y_offset, velocity);  //move right front leg forward
  twitch(RightRearRot,   y_offset, velocity);  //move right rear leg forward
  twitch(LeftMiddleRot, -(y_offset), velocity);  //move left middle leg forward
  twitch(LeftFrontRot,     y_offset,  velocity);  //move left front leg backward
  twitch(LeftRearRot,    y_offset,  velocity);  //move left rear leg backward
  twitch(RightMiddleRot,    -(y_offset),  velocity);  //move right middle leg backward
  delay(stepDelay);
  twitch(RightFrontLift,     0,         velocity);  //lower right front leg
  twitch(RightRearTibia,    0,         velocity);  //fix right front Tibia
  twitch(LeftMiddleLift,    0,         velocity);  //lower right rear leg
  twitch(RightFrontTibia,   0,         velocity);  //fix right rear Tibia
  twitch(RightRearLift,  0,         velocity);  //lower left middle leg
  twitch(LeftMiddleTibia, 0,         velocity);  //fix left middle Tibia  
  delay(stepDelay);
  twitch(LeftFrontLift,    z_offset,  velocity);  //raise left front leg 
  twitch(LeftRearLift,   z_offset,  velocity);  //raise left rear leg
  twitch(RightMiddleLift,   z_offset,  velocity);  //raise Right middle leg
  delay(stepDelay);
  twitch(LeftFrontRot,   -(y_offset), velocity);  //move left front leg forward
  twitch(LeftRearRot,  -(y_offset), velocity);  //move left rear leg forward
  twitch(RightMiddleRot,  y_offset, velocity);  //move right middle leg forward
  twitch(RightFrontRot,      -(y_offset),  velocity);  //move right front leg backward
  twitch(RightRearRot,     -(y_offset),  velocity);  //move right rear leg backward
  twitch(LeftMiddleRot,   y_offset,  velocity);  //move left middle leg backward
  delay(stepDelay); 
  twitch(LeftFrontLift,    0,         velocity);  //lower left front leg
  twitch(LeftRearLift,   0,         velocity);  //fix left front Tibia
  twitch(RightMiddleLift,   0,         velocity);  //lower left rear leg
  twitch(LeftFrontTibia,  0,         velocity);  //fix left rear Tibia
  twitch(LeftRearTibia,   0,         velocity);  //lower right middle leg
  twitch(RightMiddleTibia,  0,         velocity);  //fix right middle Tibia
  delay(stepDelay);
}

void tripod_right(int z_offset = 30, int y_offset = 15, int velocity = 100, int stepDelay = 70){  
  twitch(LeftFrontLift,     z_offset,  velocity);  //raise left front leg 
  twitch(LeftRearLift,      z_offset,  velocity);  //raise left rear leg
  twitch(RightMiddleLift,   z_offset,  velocity);  //raise right middle leg
  delay(stepDelay);
  twitch(LeftFrontRot,      y_offset,  velocity);  //move left front leg forward
  twitch(LeftRearRot,       y_offset,  velocity);  //move left rear leg forward
  twitch(RightMiddleRot,  -(y_offset), velocity);  //move right middle leg backward
  twitch(RightFrontRot,     y_offset,  velocity);  //move right front leg forward
  twitch(RightRearRot,      y_offset,  velocity);  //move right rear leg forward
  twitch(LeftMiddleRot,   -(y_offset), velocity);  //move left middle leg backward
  delay(stepDelay);
  twitch(LeftFrontLift,     0,         velocity);  //lower left front leg
  twitch(LeftRearLift,      0,         velocity);  //lower left rear leg
  twitch(RightMiddleLift,   0,         velocity);  //lower right middle leg
  twitch(LeftFrontTibia,    0,         velocity);  //fix left front Tibia
  twitch(LeftRearTibia,     0,         velocity);  //fix left rear Tibia
  twitch(RightMiddleTibia,  0,         velocity);  //fix right middle Tibia  
  delay(stepDelay);
  twitch(RightFrontLift,    z_offset,  velocity);  //raise right front leg 
  twitch(RightRearLift,     z_offset,  velocity);  //raise right rear leg
  twitch(LeftMiddleLift,    z_offset,  velocity);  //raise left middle leg
  delay(stepDelay);
  twitch(RightFrontRot,   -(y_offset), velocity);  //move right front leg backward
  twitch(RightRearRot,    -(y_offset), velocity);  //move right rear leg backward
  twitch(LeftMiddleRot,     y_offset,  velocity);  //move left middle leg forward
  twitch(LeftFrontRot,    -(y_offset), velocity);  //move left front leg backward
  twitch(LeftRearRot,     -(y_offset), velocity);  //move left rear leg backward
  twitch(RightMiddleRot,    y_offset,  velocity);  //move right middle leg forward
  delay(stepDelay); 
  twitch(RightFrontLift,    0,         velocity);  //lower right front leg
  twitch(RightRearLift,     0,         velocity);  //lower right rear leg
  twitch(LeftMiddleLift,    0,         velocity);  //lower left middle leg
  twitch(RightFrontTibia,   0,         velocity);  //fix right front Tibia
  twitch(RightRearTibia,    0,         velocity);  //fix right rear Tibia
  twitch(LeftMiddleTibia,   0,         velocity);  //fix right middle Tibia
  delay(stepDelay);
}

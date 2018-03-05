/*********************************************************************

  Y-axis  4             1
  |        \           /
  |         \         /
  |          \-------/
  |          |       |
  |   5 -----|ZAGHEXA|----- 2
  |          |       |
  |          /-------\
  |         /         \
  |        /           \
  |       6              3
  |
  Z-axis---------------------------------X-axis
            /\
    Femmur /  \
          /    \ Tibia
  __Coxa__/      \
                 \
                  \


  Coxa Lenght = 25.0;
  Femur Lenght = 76.0;
  Tibia Lenght = 112.0;
  BodySideLength = 75.0;


  In Arduino Mega use thoes pins:
	RightFrontRot    pin(23)
	RightFrontLift   pin(25)
	RightFrontTibia  pin(27)
	RightMiddleRot   pin(29)
	RightMiddleLift  pin(31)
	RightMiddleTibia pin(33)
	RightRearRot     pin(35)
	RightRearLift    pin(37)
	RightRearTibia   pin(39)
	LeftFrontRot     pin(22)
	LeftFrontLift    pin(24)
	LeftFrontTibia   pin(26)
	LeftMiddleRot    pin(28)
	LeftMiddleLift   pin(30)
	LeftMiddleTibia  pin(32)
	LeftRearRot      pin(34)
	LeftRearLift     pin(36)
	LeftRearTibia    pin(38)

  Send these command to control the robot:
  Forward   -> f
  Backward  -> b
  Left      -> l
  Right     -> r

  Change Pattern  ->  w
  Change Axies    ->  m
  Change Speed    ->  o (Increase) - p (Decrease)
  Stop            ->  d

  More Information:
  velocity -  velocity at which to move the servo.
              velocity = 0 - Full speed, identical to write
              velocity = 1 - Minimum speed
              velocity = 255 - Maximum speed

  Wmode - Modes of Gait (A):
              Tripod  0
              Wave    1
              Ripple  2

  mode - Modes of movment(B):
              NM    0
              XYT   1
              XYR   2
              ZTR   3

  Stop (D)

  Increase Speed Level (Start)
  Decrease Speed Level (Select)
*********************************************************************/
#include <WalkingPattern.h>
#include <SoftwareSerial.h>

#define DEBUGE false

walkingPattern  _WZagHexa;
SoftwareSerial _Bluetooth(11, 12);

char data = ' ';
int velocity = 0;
int Wmode = 2;
int Mode = 0;
int speedLevel = 0;
float PosX = 0, PosY = 0, PosZ = 0, RotX = 0, RotY = 0, RotZ = 0;


void setup() {

  Serial.begin(9600);
  _Bluetooth.begin(9600);
  _WZagHexa.standUp(10);
}

void loop() {
   if (_Bluetooth.available())
    {
     data = _Bluetooth.read();
    }
    
    // Stop Seginal
    if (data == 'd')
    {
     PosX = 0, PosY = 0, PosZ = 0, RotX = 0, RotY = 0, RotZ = 0;
     _WZagHexa.write_all_ref();
    }
    else if (data == 'm')
    {
     Mode++;
     // Limitation
     if (Mode > 3)
       Mode = 0;
     data == ' ';
    }

    else if (data == 'w')
    {
     Wmode++;
     // Limitation
     if (Wmode > 2)
       Wmode = 0;
     data == ' ';
    }
    //---------------------------- Velocity code ----------------------------\\
    // De/Increase speed level
    else if (data == 'o')
    {
     // Move faster
     speedLevel++;
     if (speedLevel > 4)
       // Up Limit speed level
       speedLevel = 4;
    }
    else if (data == 'p')
    {
     // Move slower
     speedLevel--;
     if (speedLevel < 1)
       // Down Limit speed level
       speedLevel = 1;
    }
    speedSet();
  /*if (j < 2)
    {
    i++;
    if (i == 1)
    {
      _WZagHexa.standUp(50);
      speedLevel++;
      speedSet();
      delay(1000);
    }
    else if ( i > 1 && i < (20-j))
    {
      data = 'f';
      if (i == 13)
        data = 'r';
    }
    else if (i == (20-j))
    {
      _WZagHexa.standUp(50);
      delay(1000);
    }
    else if ( i > (20-j) && i < (25-j))
      data = 'r';
    else if (i == (25-j))
    {
      _WZagHexa.standUp(50);
      speedLevel++;
      speedSet();
      delay(1000);
    }
    else if ( i > (25-j) && i < (44-j))
    {
      data = 'f';
      if ( i == (37-j))
        data = 'r';
    }
    else if (i == (44-j))
    {
      _WZagHexa.standUp(50);
      delay(1000);
    }
    else if ( i > (44-j) && i < (49-j))
      data = 'l';
    else
    {
      i = 0;
      j ++;
      if (j == 2)
      {
        speedLevel = 0;
        Wmode = 2;
      }
    }
    }
    else *
  if (j < 2)
  {
    i++;
    if (i == 1)
    {
      _WZagHexa.standUp(50);
      speedLevel++;
      speedSet();
      delay(1000);
    }
    else if ( i > 1 && i < 44)
      data = 'f';
    else if (i == 44)
    {
      _WZagHexa.standUp(50);
      delay(1000);
    }
    else if ( i > 44 && i < 58)
      data = 'r';
    else if (i == 58)
    {
      _WZagHexa.standUp(50);
      speedLevel++;
      speedSet();
      delay(1000);
    }
    else if ( i > 58 && i < 100)
      data = 'f';
    else if (i == 100)
    {
      _WZagHexa.standUp(50);
      delay(1000);
    }
    else if ( i > 100 && i < 114)
      data = 'l';
    else
    {
      i = 0;
      j ++;
    }
  }*/
  //velocity = 5;
  switch (Mode)
  {
    case 0:
      normalMode();
      break;
    //----------------------------  Body tilt mode(XYT) ----------------------------\\
    // X and Y Translation
    case 1:
      transXY();
      break;
    //----------------------------  Body tilt mode(XYR) ----------------------------\\
    // X and Y Rotation
    case 2:
      rotaXY();
      break;
    //----------------------------  Body tilt mode(ZTR) ----------------------------\\
    // Z Translation and Rotation
    case 3:
      transAndrotaZ();
      break;
    default:
      //normalMode();
      break;
  }
}

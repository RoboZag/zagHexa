/*****************************************************************************
 Walking Patterns - ZagHexa
 ----------------------------
  
  This is a library for Generating a Walking Patterns for Hexa Robot 
  using FK.

  These use Forward Kinematics to move the Robot the all Directions, 18 DOF-
  3 Servo each Leg.
  
  Project: CES Graguation Project ZagHexa https://robozag.github.io/zagHexa/
  Author: 
  	Mahmoud M. Awadallh  	mahmoud.elsyed21@gmail.com
  	M. Alaa Al-Shafe'y  	3bqar10@gmail.com
  Version: 1.0
  Date: 2017
------------------------------------------------------------------------------
Copyright (c) 2017 ZagHexa, Dr.Ing. Mohammed Nour Abdelgwad Ahmed
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*****************************************************************************/

#ifndef _Servo_Control_H
#define _Servo_Control_H

// Communication Library
#include "ZagHexa_servodriver.h"

// Servo Max & Min Level that give 0 and 180 degree 
#define SERVOMIN  150
#define SERVOMAX  550

// Leges sequence in the controller 
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

// Create an object to each driver and set their addresses 
ZagHexa_servodriver controller1 = ZagHexa_servodriver(0x40);
ZagHexa_servodriver controller2 = ZagHexa_servodriver(0x41);

class Walking_Patterns
{
public:
	Walking_Patterns();
	void sitdown();
	void standup();
	void tripod_forward(int z_offset = 30, int y_offset = 15, int moveDelay = 100, int stepDelay = 70);
	void tripod_backward(int z_offset = 30, int y_offset = 15, int moveDelay = 100, int stepDelay = 70);
	void tripod_left();
	void tripod_right();
	void calibrate();
	void reset_angles();
private:
	int refAngle[18];
	int oldAngle[18];
	int newAngle[18];
	void set_refAngle();
	void init_oldAngle();
	void twitch(int servo_num, int angle, int duration = 200);
	void delay(int seconds);
	void delayMicroseconds(int seconds);
	long map(long x, long in_min, long in_max, long out_min, long out_max);
	int angle2pwm(int angle);
};

#endif

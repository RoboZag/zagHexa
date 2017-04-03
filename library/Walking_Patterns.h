#ifndef _Servo_Control_H
#define _Servo_Control_H


#include "ZagHexa_servodriver.h"

#define SERVOMIN  150
#define SERVOMAX  550

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

ZagHexa_servodriver pwm = ZagHexa_servodriver(0x40);
ZagHexa_servodriver pwm1 = ZagHexa_servodriver(0x41);

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
private:
	int refAngle[18];
	int oldAngle[18];
	int newAngle[18];
	void set_refAngle();
	void init_oldAngle();
	void reset_angles();
	void calibrate();
	void twitch(int servo_num, int angle, int duration = 200);
	void delay(int seconds);
	void delayMicroseconds(int seconds);
	long map(long x, long in_min, long in_max, long out_min, long out_max);
	int angle2pwm(int angle);
};

#endif
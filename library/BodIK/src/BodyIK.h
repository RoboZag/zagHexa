////////////////////////
// ZagHexa configuration
////////////////////////

/*  Y-axis
*  ^		3			  0
*  |        \           /
*  |         \         /
*  |          \-------/
*  |          |       |
*  |   4 -----|ZAGHEXA|----- 1
*  |          |       |
*  |          /-------\
*  |         /         \
*  |        /           \
*  |       5              2
*  |
*  x ---------------------------------- >X-axis
* Z-axis
*            /\
*    Femmur /  \
*          /    \ Tibia
* __Coxa__/      \
*                 \
*                  \
*
* Coxa Lenght = 12.0;
* Femur Lenght = 35.0;
* Tibia Lenght = 72.0;
* BodySideLength = 45.0;
*
*/

#ifndef BodyIK_H
#define BodyIK_H

#include <math.h>
#include <VarSpeedServo.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define DEBUGE false
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
#define PI 3.1415926535897932384626433832795


class BodyIk {

private:
	VarSpeedServo   _Servo[18];
	float IKanglesi[18];
	float Bodyi[18];
	float feetpos[4];
	float angle[3];
public:
	BodyIk();
	float Coxa = 25.0;// in mm
	float Femur = 76.0;// in mm
	float Tibia = 112.0;// in mm
	float BodySideLength = 75.0;
	float BodyCenterOffset1 = BodySideLength / 2;
	float BodyCenterOffset2 = sqrt((BodySideLength * BodySideLength) - (BodyCenterOffset1 * BodyCenterOffset1));
	int refAngle[18];
	int    velocity;
	void attch_servo();
	//void write_all_ref(int val = 255);
	void write_ref(int, bool wait= false);
	void initialize_servos(int);
	void BodyIk::twitch(int legNum,int offset, bool wait = false);
	void trans_rotat(int,float,float,float,float,float,float);
	float* correct_angle(int Leg_num);
	void Body(float Pos[], float feetposx, float feetposy, float BodyCenterOffsetx, float BodyCenterOffset, int legNum);
	void clacHexaBodyIK(float PosX, float PosY, float PosZ, float RotX, float RotY, float RotZ);
	void Leg(float Pos[], float feetposX, float feetposY, int angle, int legNum);
};

#endif // !BodyIK_H

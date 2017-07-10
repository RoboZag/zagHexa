#ifndef BodyIK_H
#define BodyIK_H

#include <math.h>

#define Debuge false
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
	
	float feetpos[5];
	int refAngle[18];
	float* IKanglesi;
	float* Bodyi;
	float* angle;
	
public:
	float Coxa = 12;
	float Femur = 35;
	float Tibia = 72;
	float BodySideLength;
	float BodyCenterOffset1;
	float BodyCenterOffset2;
	float* IKangles[6];
	~BodyIk();
	float* correct_angle(int Leg_num);
	void calibration();
	float* Body(float Pos[], float feetposx, float feetposy, float BodyCenterOffsetx, float BodyCenterOffsety);
	void clacHexaBodyIK(float PosX, float PosY, float PosZ, float RotX, float RotY, float RotZ);
	float* Leg(float* BodyI[], float Pos[], float feetposX, float feetposY, int angle);
};

#endif // !BodyIK_H

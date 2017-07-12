#ifndef BodyIK_H
#define BodyIK_H

#include <math.h>
#include <vector>

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
#define PI 3.14159265358979323846

typedef std::vector<float> vec_float;

class BodyIk {
	
private:
	float feetpos[5];
	int refAngle[18];
	
public:
	float Coxa;
	float Femur;
	float Tibia;
	float BodyCenterOffset1;
	float BodyCenterOffset2;
	float BodySideLength;
	vec_float IKangles[6];
	vec_float correct_angle(int Leg_num);
	void calibration();
	vec_float Body(float Pos[], float feetposx, float feetposy, float BodyCenterOffsetx, float BodyCenterOffsety);
	void clacHexaBodyIK(float PosX, float PosY, float PosZ, float RotX, float RotY, float RotZ);
	vec_float Leg(vec_float BodyI[], float Pos[], float feetposX, float feetposY, int angle);
};

#endif // !BodyIK_H

#include <BodyIK.h>

// Origin
BodyIk::BodyIk()
{
	int angle = 60;
	feetpos[0] = cos(angle * PI / 180)*(Coxa + Femur);   	// feetposX_0, feetposX_2, -feetposX_3, -feetposX_5
	feetpos[1] = sin(angle * PI / 180)*(Coxa + Femur);   	// feetposY_0, -feetposY_2,feetposY_3,-feetposY_5
	feetpos[2] = Tibia;										// feetposZ_All
	feetpos[3] = Coxa + Femur;								// feetposX_1, -feetposX_4

	// Set the stand up angles
	/*************************************************************************************************************************
		--------------------------				--------------------------				-------------------------------	
		Right Leg Up   90 - Theta				 Right Leg In  90 - Theta				 Right Leg Forward  90 - Theta
		Right Leg Down 90 + Theta				 Right Leg Out 90 + Theta				 Right Leg Backward 90 + Theta
		--------------------------				--------------------------				-------------------------------
		--------------------------				--------------------------				-------------------------------	
		Left Leg Up   90 + Theta				 Left Leg In  90 + Theta				 Left Leg Forward  90 + Theta
		Left Leg Down 90 - Theta				 Left Leg Out 90 - Theta				 Left Leg Backward 90 - Theta
		--------------------------				--------------------------				-------------------------------
	*************************************************************************************************************************/
	refAngle[RightFrontRot] 	= 90;
	refAngle[RightFrontLift]	= 95;
	refAngle[RightFrontTibia] 	= 85;
	refAngle[RightMiddleRot] 	= 90;
	refAngle[RightMiddleLift] 	= 90;
	refAngle[RightMiddleTibia] 	= 90;
	refAngle[RightRearRot] 		= 90;
	refAngle[RightRearLift] 	= 95;
	refAngle[RightRearTibia] 	= 90;
	refAngle[LeftFrontRot] 		= 90;
	refAngle[LeftFrontLift] 	= 80;
	refAngle[LeftFrontTibia] 	= 90;
	refAngle[LeftMiddleRot] 	= 90;
	refAngle[LeftMiddleLift] 	= 90;
	refAngle[LeftMiddleTibia] 	= 90;
	refAngle[LeftRearRot] 		= 90;
	refAngle[LeftRearLift] 		= 80;
	refAngle[LeftRearTibia] 	= 90;

}

// Rotation 
void BodyIk::Body(float Pos[], float feetposx, float feetposy, float BodyCenterOffsetx, float BodyCenterOffsety, int legNum) {

	float CrotX = cos(Pos[3] * PI / 180);
	float SrotX = sin(Pos[3] * PI / 180);
	float CrotY = cos(Pos[4] * PI / 180);
	float SrotY = sin(Pos[4] * PI / 180);
	float CrotZ = cos(Pos[5] * PI / 180);
	float SrotZ = sin(Pos[5] * PI / 180);

	float TotalX_1 = feetposx + BodyCenterOffsetx + Pos[0];
	float TotalY_1 = feetposy + BodyCenterOffsety + Pos[1];
	
	Bodyi[legNum*3] 	= (TotalX_1*CrotY*CrotZ - TotalY_1*CrotY*SrotZ + feetpos[2] * SrotY - TotalX_1);
	
	Bodyi[legNum*3 + 1] = (TotalX_1*CrotX*SrotZ + TotalX_1*CrotZ*SrotY*SrotX + TotalY_1*CrotZ*CrotX -
						   TotalY_1*SrotZ*SrotY*SrotX - feetpos[2] * CrotY*SrotX) - TotalY_1;
	
	Bodyi[legNum*3 + 2] = (TotalX_1*SrotZ*SrotX - TotalX_1*CrotZ*CrotX*SrotY + TotalY_1*CrotZ*SrotX +
						   TotalY_1*CrotX*SrotZ*SrotY + feetpos[2] * CrotY*CrotX) - feetpos[2];
}

// Transition
void BodyIk::Leg(float Pos[], float feetposX, float feetposY, int angle, int legNum)
{

	
	float NewPosX = feetposX   + Pos[0] + Bodyi[legNum*3    ];
	float NewPosY = feetposY   + Pos[1] + Bodyi[legNum*3 + 1];
	float NewPosZ = feetpos[2] + Pos[2] + Bodyi[legNum*3 + 2];

	float TranformX = (NewPosX * sin(angle * PI / 180)) - (NewPosY * cos(angle * PI / 180)); 
	float TranformY = (NewPosX * cos(angle * PI / 180)) + (NewPosY * sin(angle * PI / 180));

	float CoxaFeetDist = sqrt((NewPosX * NewPosX) + (NewPosY * NewPosY));
	float HF = sqrt(((CoxaFeetDist - Coxa) * (CoxaFeetDist - Coxa)) + (NewPosZ *NewPosZ));
	float IKA1 = atan((CoxaFeetDist - Coxa) / NewPosZ);
	float IKA2 = acos(((Tibia * Tibia) - (Femur *Femur) - (HF * HF)) / (-2 * HF *Femur));
	float B_1 = acos(((HF * HF) - (Tibia * Tibia) - (Femur *Femur)) / (-2 * Femur *Tibia));

	float IKTibiaAngle = 90 - (B_1 * 180 / PI);
	float IKFemurAngle = ((IKA1 + IKA2) * 180 / PI) - 90;
	float IKCoxaAngle = ((atan2(TranformX, TranformY) * 180) / PI);

	IKanglesi[legNum*3 + 2] = (IKTibiaAngle);
	IKanglesi[legNum*3 + 1] = (IKFemurAngle);
	IKanglesi[legNum*3    ] = (IKCoxaAngle);
}

void BodyIk::clacHexaBodyIK(float PosX, float PosY, float PosZ, float RotX, float RotY, float RotZ)
{
	float Pos[6];
	
	// Input postions and angles
	Pos[0] = PosX*2; Pos[1] = PosY; Pos[2] = PosZ;	Pos[3] = RotX;	Pos[4] = RotY;	Pos[5] = RotZ;

	// Body IK
	Body(Pos,  feetpos[0],  feetpos[1],  BodyCenterOffset1,  BodyCenterOffset2, 0);
	Body(Pos,  feetpos[3],  0         ,  BodySideLength   ,  0                , 1);
	Body(Pos,  feetpos[0], -feetpos[1],  BodyCenterOffset1, -BodyCenterOffset2, 2);
	Body(Pos, -feetpos[0],  feetpos[1], -BodyCenterOffset1,  BodyCenterOffset2, 3);
	Body(Pos, -feetpos[3],  0         , -BodySideLength   ,  0                , 4);
	Body(Pos, -feetpos[0], -feetpos[1], -BodyCenterOffset1, -BodyCenterOffset2, 5);

	// Leg IK
	Leg(Pos,  feetpos[0],  feetpos[1], 60  , 0);
	Leg(Pos,  feetpos[3],  0         , 0   , 1);
	Leg(Pos,  feetpos[0], -feetpos[1], 300 , 2);
	Leg(Pos, -feetpos[0],  feetpos[1], 120 , 3);
	Leg(Pos, -feetpos[3],  0         , 180 , 4);
	Leg(Pos, -feetpos[0], -feetpos[1], 240 , 5);
}
/*
0 RightFront  1 RightMiddle  2 RightRear

3 LeftFront   4 LeftMiddle   5 LeftRear
*/
float* BodyIk::correct_angle(int Leg_num) {
	// Return the angle which the Servo will move according to it (Coxa, Fummer, Tibia)
	if (Leg_num >= 0 && Leg_num < 3) 
	{
		
		angle[2] = (refAngle[Leg_num * 3 + 2] + IKanglesi[Leg_num*3 + 2]); // Tibia Angel for the second 3 Legs	
		
		angle[1] = (refAngle[Leg_num * 3 + 1] + IKanglesi[Leg_num*3 + 1]); // Femmur Angel for the first 3 Legs
		
		angle[0] = (refAngle[Leg_num * 3]     + IKanglesi[Leg_num*3]); // Coxa Angel for the second 3 Legs
	
	}	
	else if (Leg_num >= 3 && Leg_num < 6) 
	{
		angle[2] = (refAngle[Leg_num * 3 + 2] - IKanglesi[Leg_num*3 + 2]); // Tibia Angel for the second 3 Legs	
		
		angle[1] = (refAngle[Leg_num * 3 + 1] - IKanglesi[Leg_num*3 + 1]); // Femmur Angel for the second 3 Legs
	
		angle[0] = (refAngle[Leg_num * 3]     + IKanglesi[Leg_num*3]); // Coxa Angel for the second 3 Legs
	}
	
	return angle;
}


#include <BodyIK.h>

vec_float BodyIk::Body(float Pos[],float feetposx, float feetposy,float BodyCenterOffsetx, float BodyCenterOffsety){
	
	vec_float Body;
	vec_float::iterator ins = Body.begin();

	double CrotX = cos(Pos[3] * PI / 180);
	double SrotX = sin(Pos[3] * PI / 180);
	double CrotY = cos(Pos[4] * PI / 180);
	double SrotY = sin(Pos[4] * PI / 180);
	double CrotZ = cos(Pos[5] * PI / 180);
	double SrotZ = sin(Pos[5] * PI / 180);

	float TotalX_1 = feetposx + BodyCenterOffsetx + Pos[0];
	float TotalY_1 = feetposy + BodyCenterOffsety + Pos[1];

	
	ins = Body.insert(ins, TotalX_1*CrotY*CrotZ - TotalY_1*CrotY*SrotZ + feetpos[2] * SrotY - TotalX_1);
	
	ins = Body.insert(ins,( TotalX_1*CrotX*SrotZ + TotalX_1*CrotZ*SrotY*SrotX + TotalY_1*CrotZ*CrotX -
		       TotalY_1*SrotZ*SrotY*SrotX - feetpos[2] * CrotY*SrotX) - TotalY_1);

	ins = Body.insert(ins, (TotalX_1*SrotZ*SrotX - TotalX_1*CrotZ*CrotX*SrotY + TotalY_1*CrotZ*SrotX +
	     	   TotalY_1*CrotX*SrotZ*SrotY + feetpos[2] * CrotY*CrotX) - feetpos[2]);
	
	return Body;
}

vec_float BodyIk::Leg(vec_float BodyI[], float Pos[], float feetposX, float feetposY, int angle)
{
	vec_float IKangles;

	float NewPosX = feetposX   + Pos[0] + BodyI[0][2];
	float NewPosY = feetposY   + Pos[1] + BodyI[0][1];
	float NewPosZ = feetpos[2] + Pos[2] + BodyI[0][0];

	float TranformX = NewPosX * cos(angle * PI / 180) - NewPosY * sin(angle * PI / 180);
	float TranformY = NewPosX * sin(angle * PI / 180) + NewPosY * cos(angle * PI / 180);

	float CoxaFeetDist = sqrt((NewPosX * NewPosX) + (NewPosY * NewPosY));
	float IKSW = sqrt(((CoxaFeetDist - Coxa) * (CoxaFeetDist - Coxa)) + (NewPosZ *NewPosZ));
	float IKA1 = atan((CoxaFeetDist - Coxa) / NewPosZ);
	float IKA2 = acos(((Tibia * Tibia) - (Femur *Femur) - (IKSW * IKSW)) / (-2 * IKSW *Femur));
	float TAngle = acos(((IKSW * IKSW) - (Tibia * Tibia) - (Femur *Femur)) / (-2 * Femur *Tibia));
	
	float IKTibiaAngle = 90 - (TAngle * 180 / PI);
	float IKFemurAngle = ((IKA1 + IKA2)* 180 / PI) - 90;
	float IKCoxaAngle = ((atan2(TranformX, TranformY) * 180 )/ PI);


	// Deal with is like stake Last in first out LIFO
	IKangles.push_back(IKTibiaAngle);
	IKangles.push_back(IKFemurAngle);
	IKangles.push_back(IKCoxaAngle);
	
	return IKangles;
}

void BodyIk::clacHexaBodyIK(float PosX, float PosY, float PosZ, float RotX, float RotY, float RotZ)
{
	float Pos[6];
	vec_float BodyI[6];
	int angle = 60;

	feetpos[0] = cos(angle * PI /180)*(Coxa + Femur);   // feetposX_1, feetposX_3, -feetposX_4, -feetposX_6
	feetpos[1] = sin(angle * PI /180)*(Coxa + Femur);   // feetposY_1, feetposY_6
	feetpos[2] = Tibia;									// feetposZ_All
	feetpos[3] = Coxa + Femur;							// feetposX_2, -feetposX_5
	feetpos[4] = sin(-angle * PI /180)*(Coxa + Femur);  // feetposY_3, feetposY_4
	
	// Input postions 
	Pos[0] = PosX; 	Pos[1] = PosY; Pos[2] = PosZ;	Pos[3] = RotX;	Pos[4] = RotY;	Pos[5] = RotZ;
	
	// Body IK
	BodyI[0] = Body(Pos,  feetpos[0], feetpos[1],  BodyCenterOffset1,  BodyCenterOffset2 );
	BodyI[1] = Body(Pos,  feetpos[3], 0	  		,  BodySideLength   ,  0   		    	 );
	BodyI[2] = Body(Pos,  feetpos[0], feetpos[4],  BodyCenterOffset1, -BodyCenterOffset2 );
	BodyI[3] = Body(Pos, -feetpos[0], feetpos[4], -BodyCenterOffset1, -BodyCenterOffset2 );
	BodyI[4] = Body(Pos, -feetpos[3], 0	    	, -BodySideLength   ,  0		   		 );
	BodyI[5] = Body(Pos, -feetpos[0], feetpos[1], -BodyCenterOffset1,  BodyCenterOffset2 );

	// Leg IK
	IKangles[0] = Leg(&BodyI[0], Pos,  feetpos[0], feetpos[1], 30);
	IKangles[1] = Leg(&BodyI[1], Pos,  feetpos[3], 0         , 90);
	IKangles[2] = Leg(&BodyI[2], Pos,  feetpos[0], feetpos[4], 150);
	IKangles[3] = Leg(&BodyI[3], Pos, -feetpos[0], feetpos[4], 210);
	IKangles[4] = Leg(&BodyI[4], Pos, -feetpos[3], 0         , 270);
	IKangles[5] = Leg(&BodyI[5], Pos, -feetpos[0], feetpos[1], 330);
	
	/*
	for (int j = 0; j < 6; j++)
	{
		for (vec_float::iterator i = IKangles[j].begin(); i != IKangles[j].end(); i++)
		{
			std::cout << *(i) << "\n";
		}

	}
	
	

	int x;
	std::cin >> x;*/

}

void BodyIk::calibration()
{
	// Set the stand up angles
	refAngle[RightFrontRot] = 90;
	refAngle[RightFrontLift] = 95;
	refAngle[RightFrontTibia] = 92;
	refAngle[RightMiddleRot] = 90;
	refAngle[RightMiddleLift] = 93;
	refAngle[RightMiddleTibia] = 98;
	refAngle[RightRearRot] = 90;
	refAngle[RightRearLift] = 88;
	refAngle[RightRearTibia] = 98;
	refAngle[LeftFrontRot] = 90;
	refAngle[LeftFrontLift] = 84;
	refAngle[LeftFrontTibia] = 98;
	refAngle[LeftMiddleRot] = 90;
	refAngle[LeftMiddleLift] = 90;
	refAngle[LeftMiddleTibia] = 98;
	refAngle[LeftRearRot] = 90;
	refAngle[LeftRearLift] = 83;
	refAngle[LeftRearTibia] = 95;
	
}

/*
	0 RightFront
	1 RightMiddle
	2 RightRear
	3 LeftFront
	4 LeftMiddle
	5 LeftRear

*/
vec_float BodyIk::correct_angle(int Leg_num) {
	// Return the angle which the Servo will move according to it (Coxa, Fumer, Tibia)
	vec_float angle;
	if (Leg_num >= 0 && Leg_num < 3) {

		// Deal with is like stake Last in first out LIFO
		angle.push_back(refAngle[Leg_num + 2] - IKangles[Leg_num][2]); // Tibia Angel for the first 3 Legs

		angle.push_back(refAngle[Leg_num + 1] - IKangles[Leg_num][1]); // Femur Angel for the first 3 Legs

		angle.push_back(refAngle[Leg_num] - IKangles[Leg_num][0]);	   // Coxa Angel for the first 3 Legs

	}
	else if (Leg_num >= 3 && Leg_num < 6) {

		angle.push_back(refAngle[Leg_num + 2] + IKangles[Leg_num][2]); // Tibia Angel for the second 3 Legs	

		angle.push_back(refAngle[Leg_num + 1] + IKangles[Leg_num][1]); // Femur Angel for the second 3 Legs

		angle.push_back(refAngle[Leg_num] + IKangles[Leg_num][0]);     // Coxa Angel for the second 3 Legs


	}
	// Return vector containe the 3 angles for the wanted leg 
	return angle;
}


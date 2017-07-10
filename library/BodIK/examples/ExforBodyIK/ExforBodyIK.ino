#include <BodyIK.h>

  /*
    0 RightFront
    1 RightMiddle
    2 RightRear
    3 LeftFront
    4 LeftMiddle
    5 LeftRear

  */
  

BodyIk Hexa;

void setup(){
  Serial.begin(9600);
}
void loop(){
  
	Hexa.Coxa = 12.0;
	Hexa.Femur = 35.0;
	Hexa.Tibia = 72.0;
	Hexa.BodySideLength = 80.0;
	Hexa.BodyCenterOffset1 = Hexa.BodySideLength / 2;
	Hexa.BodyCenterOffset2 = sqrt((Hexa.BodySideLength * Hexa.BodySideLength) - (Hexa.BodyCenterOffset1 * Hexa.BodyCenterOffset1));

  // Set the refrance angles to the servo 
	Hexa.calibration();
  // Hexa.clacHexaBodyIK(PosX, PosY, PosZ, RotX, RotY, RotZ);
  // Left the leg and move 5mm forward
	Hexa.clacHexaBodyIK(5, 0, 5,0,0,0);
	
	// The frist angle for the frist leg 
  Serial.print (Hexa.IKangles[0][0]); Serial.print("\n");
}	

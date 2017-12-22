#include "WalkingPattern.h"

void walkingPattern::attch_servo(){
	_Servo[RightFrontRot]	.attach(22);
	_Servo[RightFrontLift]  .attach(24);
	_Servo[RightFrontTibia] .attach(26);
	_Servo[RightMiddleRot]  .attach(28);
	_Servo[RightMiddleLift] .attach(30);
	_Servo[RightMiddleTibia].attach(32);
	_Servo[RightRearRot]    .attach(34); 
	_Servo[RightRearLift]	.attach(36); 
	_Servo[RightRearTibia]  .attach(38);
	_Servo[LeftFrontRot]    .attach(23); 
	_Servo[LeftFrontLift]   .attach(25); 
	_Servo[LeftFrontTibia]  .attach(27);
	_Servo[LeftMiddleRot]   .attach(29); 
	_Servo[LeftMiddleLift]  .attach(31); 
	_Servo[LeftMiddleTibia] .attach(33);
	_Servo[LeftRearRot]     .attach(35); 
	_Servo[LeftRearLift]    .attach(37); 
	_Servo[LeftRearTibia]   .attach(39);
	
}

void walkingPattern::twitch(int legNum,int offset, bool wait = false){
	float* newAngle;
	newAngle = _zagHexa_.correct_angle(legNum);							// Coxa[0], Femmur[1], Tibia[2]
	_Servo[legNum*3 + offset].write(floor(newAngle[offset]), velocity, wait);	
}

void walkingPattern::write_all_ref(int val = 255){
	trans_rotat(val,0,0,0,0,0,0);
}


void walkingPattern::write_ref(int servo, bool wait = false){
	_Servo[servo].write(_zagHexa_.refAngle[servo], velocity, wait);
}

void walkingPattern::trans_rotat(int val,float PosX,float PosY, float PosZ,float RotX, float RotY, float RotZ){
	float * angle;
	_zagHexa_.clacHexaBodyIK(PosX, PosY, PosZ, RotX, RotY, RotZ);
	for( byte legNum = 0; legNum < 6; legNum++)
	{
		angle = _zagHexa_.correct_angle(legNum);
		for(int offset=0; offset<3; offset++)
		_Servo[legNum*3 +offset].write(floor(angle[offset]), val, true);
	}
}

void walkingPattern::forward(int vel,int mode){  
	velocity = vel;
	switch(mode)
	{
		case 0:
			for(byte i=0; i<2;i++)
			{
				// Up 
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				twitch(RightRear    + i, Up_Down);						// Rise Right/Left 	Rear/Front   Leg
				twitch(RightFront   + i, Up_Down);						// Rise Right 		Front/Middle Leg
				twitch(LeftMiddle 	+ i, Up_Down, true);				// Rise Left 		Middle/Rear  Leg and wait until done
		
				// Forward
				_zagHexa_.clacHexaBodyIK(0,yShift/2,0,0,0,0);
				twitch(RightFront   + i, Forward_Backward);         	// Move Right  		Front/Middle  Leg forward
				twitch(RightRear    + i, Forward_Backward);				// Move Right/Left  Rear/Front    Leg forward
				twitch(LeftMiddle  + i, Forward_Backward, true);		// Move Left 		Middle/Rear   Leg forward and wait until done
			
				// Backward
				_zagHexa_.clacHexaBodyIK(0,-yShift,0,0,0,0);
				twitch(LeftFront  	 - i, Forward_Backward);			// Move Left 		Middle/Front Leg backward
				twitch(LeftRear    	 - i, Forward_Backward);			// Move Left/Left   Front/Rear   Leg backward
				twitch(RightMiddle   - i, Forward_Backward, true);		// Move Right 		Rear/Middle  Leg backward and wait until done
	
				// Down
				write_ref((RightFront   + i)*3   + Up_Down);			// Land Right 		Front/Middle Leg
				write_ref((RightRear    + i)*3   + Up_Down);			// Land Right/Left  Rear/Front   Leg
				write_ref((LeftMiddle	+ i)*3   + Up_Down, true);		// Land Left 		Middle/Rear  Leg and wait until done
			}
		break;
		
		case 1:
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				if( i == 0 )
				{
					twitch(RightFront  , Up_Down);						// Rise Right	Front Leg
					twitch(LeftRear    , Up_Down,true);					// Rise Left	Rear  Leg and wait until done
				}
				else if( i == 2)
				{
					twitch(RightMiddle , Up_Down);						// Rise Right	Middle Leg
					twitch(LeftFront   , Up_Down,true);					// Rise Left	Front  Leg and wait until done					
				}
				else if( i == 1)
				{
					twitch(RightRear   , Up_Down);						// Rise Right	Rear   Leg
					twitch(LeftMiddle  , Up_Down,true);					// Rise Left	Middle Leg and wait until done
				}
				else
				{
					/* Do nothing */
				}
			
				// Forward
				_zagHexa_.clacHexaBodyIK(0,yShift/2,0,0,0,0);
				if( i == 0 )
				{
					twitch(RightFront  , Forward_Backward);				// Move Right Front Leg forward
					twitch(LeftRear    , Forward_Backward,true);		// Move Left  Rear  Leg forward and wait until done
				}
				else if( i == 2)
				{
					twitch(RightMiddle , Forward_Backward);				// Move Right Middle Leg forward
					twitch(LeftFront   , Forward_Backward,true);		// Move Left  Front  Leg forward and wait until done			
				}
				else if( i == 1)
				{
					twitch(RightRear   , Forward_Backward);				// Move Right Rear   Leg forward
					twitch(LeftMiddle  , Forward_Backward,true);		// Move Left  Middle Leg forward and wait until done
				
				}
				else
				{
					/* Do nothing */
				}
				
				// Backward
				_zagHexa_.clacHexaBodyIK(0,-yShift,0,0,0,0);
				if( i == 0)
				{
					twitch(LeftFront   , Forward_Backward);				// Move Left  Front   Leg backward
					twitch(LeftMiddle  , Forward_Backward);				// Move Left  Middle  Leg backward
					twitch(RightMiddle , Forward_Backward);				// Move Right Middle  Leg backward
					twitch(RightRear   , Forward_Backward, true);		// Move Right Rear    Leg backward and wait until done
				}
				else if( i == 2)
				{
					twitch(LeftMiddle  , Forward_Backward);				// Move Left  Middle Leg backward
					twitch(LeftRear    , Forward_Backward);				// Move Left  Rear   Leg backward
					twitch(RightRear   , Forward_Backward);				// Move Right Rear   Leg backward
					twitch(RightFront  , Forward_Backward, true);		// Move Right Front  Leg backward and wait until done
				}
				else if( i == 1)
				{
					twitch(LeftRear    , Forward_Backward);				// Move Left  Rear    Leg backward
					twitch(LeftFront   , Forward_Backward);				// Move Left  Front   Leg backward 
					twitch(RightFront  , Forward_Backward);				// Move Right Front   Leg backward
					twitch(RightMiddle , Forward_Backward, true);		// Move Right Middle  Leg backward and wait until done
				
				}
				else
				{
					/* Do nothing */
				}
				
				// Down and move back
				if( i == 0 )
				{
					write_ref((RightFront )*3   + Up_Down);					// Land Right Front  Leg
					write_ref((LeftRear	  )*3   + Up_Down);					// Land Left  Rear   Leg 
					write_ref((RightRear  )*3   + Forward_Backward);		// Move Right Rear   Leg backward
					write_ref((LeftMiddle )*3   + Forward_Backward,true);	// Move Left  Middle Leg backward and wait until done
					
				}
				else if( i == 2)
				{	
					write_ref((RightMiddle)*3   + Up_Down);					// Land Right Middle Leg
					write_ref((LeftFront  )*3   + Up_Down);					// Land Left  Front  Leg 
					write_ref((RightFront )*3   + Forward_Backward);		// Move Right Front  Leg backward
					write_ref((LeftRear   )*3   + Forward_Backward,true);	// Move Left  Rear   Leg backward and wait until done
				}
				else if( i == 1)
				{
					write_ref((RightRear  )*3   + Up_Down);					// Land Right 		Rear   Leg
					write_ref((LeftMiddle )*3   + Up_Down);					// Land Left 		Middle Leg 
					write_ref((RightMiddle)*3   + Forward_Backward);		// Move Right 		Middle Leg backward
					write_ref((LeftFront  )*3   + Forward_Backward,true);	// Move Left 		Front  Leg backward and wait until done
					
				}
				else
				{
					/* Do nothing */
				}
			}/*
			for(int servoNum = 0; servoNum <= 15;)
			{
				write_ref(servoNum);
				servoNum +=3;
			}*/
		break;

		case 2:
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				twitch(LeftFront + i, Up_Down,true);					// Rise Legs From LeftFront to LeftRear
				
				// Forward
				_zagHexa_.clacHexaBodyIK(0,yShift,0,0,0,0);
				twitch(LeftFront  + i, Forward_Backward, true);			// Move Legs From LeftFront to LeftRear forward 
				
				// Down
				write_ref((LeftFront + i)*3   + Up_Down, true);			// Land Legs From LeftFront to LeftRear 

			}
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				twitch(RightFront + i, Up_Down,true);					// Rise Legs From RightFront to RightRear 
				
				// Forward
				_zagHexa_.clacHexaBodyIK(0,yShift,0,0,0,0);
				twitch(RightFront  + i, Forward_Backward, true);		// Move Legs From RightFront to RightRar forward 
				
				// Down
				write_ref((RightFront + i)*3   + Up_Down, true);		// Land Legs From RightFront to RightRear 
				
			}
			for(int servoNum = 0; servoNum <= 15;)
			{
				write_ref(servoNum);									// Move all Coxa to the zero position
				servoNum +=3;
			}
		break;
			
			
	}
}	



void walkingPattern::backword(int vel, int mode){  
	velocity = vel;
	
	switch(mode)
	{
		case 0:
			for(int i=0; i <2; i++)
			{
				// Up 
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				twitch(RightFront   + i, Up_Down);						// Rise Right 		Front/Middle Leg
				twitch(RightRear    + i, Up_Down);						// Rise Right/Left 	Rear/Front   Leg
				twitch(LeftMiddle 	+ i, Up_Down, true);				// Rise Left 		Middle/Rear  Leg and wait until done
				
				// Backward
				_zagHexa_.clacHexaBodyIK(0,-yShift/2,0,0,0,0);
				twitch(RightFront   + i, Forward_Backward);          	// Move Right  		Front/Middle  Leg backward
				twitch(RightRear    + i, Forward_Backward);				// Move Right/Left  Rear/Front    Leg backward
				twitch(LeftMiddle   + i, Forward_Backward, true);		// Move Right 		Middle/Rear   Leg backward and wait until done
				
				// Forward
				_zagHexa_.clacHexaBodyIK(0,yShift,0,0,0,0);
				twitch(LeftFront  	 - i, Forward_Backward);			// Move Left 		Middle/Front Leg forward
				twitch(LeftRear    	 - i, Forward_Backward);			// Move Left/Left   Front/Rear   Leg forward
				twitch(RightMiddle   - i, Forward_Backward, true);		// Move Right 		Rear/Middle  Leg forward and wait until done
			
				// Down
				write_ref((RightFront   + i)*3   + Up_Down);			// Land Right 		Front/Middle Leg
				write_ref((RightRear    + i)*3   + Up_Down);			// Land Right/Left  Rear/Front   Leg
				write_ref((LeftMiddle	+ i)*3   + Up_Down, true);		// Land Left 		Middle/Rear Leg and wait until done
			
			}
		break;
		
		case 1:
		for(byte i=0; i<3; i++)
			{
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				if( i == 0 )
				{
					twitch(RightFront  , Up_Down);						// Rise Right	Front Leg
					twitch(LeftRear    , Up_Down,true);					// Rise Left	Rear  Leg and wait until done
				}
				else if( i == 2)
				{
					twitch(RightRear   , Up_Down);						// Rise Right	Rear   Leg
					twitch(LeftMiddle  , Up_Down,true);					// Rise Left	Middle Leg and wait until done
				}
				else if( i == 1)
				{
					twitch(RightMiddle , Up_Down);						// Rise Right	Middle Leg
					twitch(LeftFront   , Up_Down,true);					// Rise Left	Front  Leg and wait until done
				}
				else
				{
					/* Do nothing */
				}
		
				// Backward
				_zagHexa_.clacHexaBodyIK(0,-yShift/2,0,0,0,0);
				if( i == 0 )
				{
					twitch(RightFront  , Forward_Backward);				// Move Right  Front  Leg backward
					twitch(LeftRear    , Forward_Backward,true);		// Move Left   Rear   Leg backward and wait until done
				}
				else if( i == 2)
				{
					twitch(RightRear   , Forward_Backward);				// Move Right  Rear   Leg backward
					twitch(LeftMiddle  , Forward_Backward,true);		// Move Left   Middle Leg backward and wait until done
				}
				else if( i == 1)
				{
					twitch(RightMiddle , Forward_Backward);				// Move Right  Middle Leg backward
					twitch(LeftFront   , Forward_Backward,true);		// Move Left   Front  Leg backward and wait until done
				}
				else
				{
					/* Do nothing */
				}
				
				// Forward
				_zagHexa_.clacHexaBodyIK(0,yShift,0,0,0,0);
				if( i == 0)
				{
					twitch(LeftFront   , Forward_Backward);				// Move Left  Front  Leg forward
					twitch(LeftMiddle  , Forward_Backward);				// Move Left  Middle Leg forward
					twitch(RightMiddle , Forward_Backward);				// Move Right Middle Leg forward
					twitch(RightRear   , Forward_Backward, true);		// Move Right Rear   Leg forward and wait until done
				}
				else if( i == 2)
				{
					twitch(LeftFront   , Forward_Backward);				// Move Left  Front  Leg forward
					twitch(LeftRear    , Forward_Backward);				// Move Left  Rear   Leg forward
					twitch(RightMiddle , Forward_Backward);				// Move Right Middle Leg forward
					twitch(RightFront  , Forward_Backward, true);		// Move Right Front  Leg forward and wait until done
				}
				else if( i == 1)
				{
					twitch(LeftRear    , Forward_Backward);				// Move Left  Rear   Leg forward
					twitch(LeftMiddle  , Forward_Backward);				// Move Left  Middle Leg forward
					twitch(RightFront  , Forward_Backward);				// Move Right Front  Leg forward
					twitch(RightRear   , Forward_Backward, true);		// Move Right Rear   Leg forward and wait until done
				}
				else
				{
					/* Do nothing */
				}
				// Down
				if( i == 0 )
				{
					write_ref((RightFront )*3   + Up_Down);					// Land Right Front  Leg
					write_ref((LeftRear	  )*3   + Up_Down);					// Land Left  Rear   Leg
					write_ref((RightMiddle)*3   + Forward_Backward);		// Move Right Middle Leg forward
					write_ref((LeftFront  )*3   + Forward_Backward,true);	// Move Left  Front  Leg forward and wait until done
				}
				else if( i == 1)
				{
					write_ref((RightMiddle)*3   + Up_Down);					// Land Right Middle Leg
					write_ref((LeftFront  )*3   + Up_Down);					// Land Left  Front  Leg
					write_ref((RightFront )*3   + Forward_Backward);		// Move Right Front  Leg forward
					write_ref((LeftRear   )*3   + Forward_Backward,true);	// Move Left  Rear   Leg forward and wait until done
				 
				}
				else if( i == 2)
				{	
					write_ref((RightRear  )*3   + Up_Down);					// Land Right Rear   Leg
					write_ref((LeftMiddle )*3   + Up_Down);					// Land Left  Middle Leg
					write_ref((RightMiddle)*3   + Forward_Backward);		// Move Right Middle Leg forward
					write_ref((LeftFront  )*3   + Forward_Backward,true);	// Move Left  Front  Leg forward and wait until done
				}
				else
				{
					/* Do nothing */
				}
				
			}
		break;

		case 2:
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				twitch(LeftFront + i, Up_Down,true);					// Rise Legs From LeftFront to LeftRear
				
				// Backward
				_zagHexa_.clacHexaBodyIK(0,-yShift,0,0,0,0);
				twitch(LeftFront  + i, Forward_Backward, true);			// Move Legs From LeftFront to LeftRear backward
				
				// Down
				write_ref((LeftFront + i)*3   + Up_Down, true);			// Land Legs From LeftFront to LeftRear

			}
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				twitch(RightFront + i, Up_Down,true);					// Rise Legs From RightFront to RightRear 
				
				// Backward
				_zagHexa_.clacHexaBodyIK(0,-yShift,0,0,0,0);
				twitch(RightFront  + i, Forward_Backward, true);		// Move Legs From RightFront to RightRear backward
				
				// Down
				write_ref((RightFront + i)*3   + Up_Down, true);		// Land Legs From RightFront to RightRear 
				
			}
			for(int servoNum = 0; servoNum <= 15;)
			{
				write_ref(servoNum);									// Move all Coxa to the zero position
				servoNum +=3;
			}
		break;
	}
}

void walkingPattern::right(int vel,int mode){  
	velocity = vel;
	
	switch(mode)
	{
		case 0:
			for(byte i=0; i<2; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				twitch(RightFront   + i, Up_Down);						// Rise Right 		Front/Middle Leg
				twitch(RightRear    + i, Up_Down);						// Rise Right/Left 	Rear/Front   Leg
				twitch(LeftMiddle 	+ i, Up_Down, true);				// Rise Left 		Middle/Rear  Leg and wait until done
				
				// Rotate right
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,-zRotation);
				twitch(RightFront   + i, Forward_Backward);         	// Rotate Left  		Front/Middle  Leg Right
				twitch(RightRear    + i, Forward_Backward);				// Rotate Left/Right	Rear/Front    Leg Right
				twitch(LeftMiddle	+ i, Forward_Backward, true);		// Rotate Right 		Middle/Rear   Leg Right and wait until done
					
				// Rotate left
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,zRotation);
				twitch(RightMiddle - i, Forward_Backward);				// Rotate Right			Middle/Front Leg Left
				twitch(LeftFront   - i, Forward_Backward);				// Rotate Left/Right  	Front/Rear   Leg Left
				twitch(LeftRear    - i, Forward_Backward, true);		// Rotate Left	 		Rear/Middle  Leg Left and wait until done
			
				// Down
				write_ref((RightFront   + i)*3   + Up_Down);			// Land Right 		Front/Middle Leg
				write_ref((RightRear    + i)*3   + Up_Down);			// Land Right/Left  Rear/Front   Leg
				write_ref((LeftMiddle	+ i)*3   + Up_Down, true);		// Land Left 		Middle/Rear Leg and wait until done
			
			}
		break;
		
		case 1:
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				if( i == 0 )
				{
					twitch(RightFront  , Up_Down);						// Rise Right 		Front/Middle Leg
					twitch(LeftRear    , Up_Down,true);					// Rise Right 		Front/Middle Leg
				}
				else if( i == 1)
				{
					twitch(RightRear   , Up_Down);		
					twitch(LeftMiddle  , Up_Down,true);
				}
				else if( i == 2)
				{
					twitch(RightMiddle , Up_Down);	
					twitch(LeftFront   , Up_Down,true);							
				}
		
				// Rotate right
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,-zRotation);
				if( i == 0 )
				{
					twitch(RightFront  , Forward_Backward);						// Rise Right 		Front/Middle Leg
					twitch(LeftRear    , Forward_Backward,true);					// Rise Right 		Front/Middle Leg
				}
				else if( i == 1)
				{
					twitch(RightRear   , Forward_Backward);		
					twitch(LeftMiddle  , Forward_Backward,true);
				}
				else if( i == 2)
				{
					twitch(RightMiddle , Forward_Backward);	
					twitch(LeftFront   , Forward_Backward,true);							
				}
				
				// Rotate left
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,zRotation);
				if( i == 0)
				{
					twitch(LeftFront   , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					twitch(LeftMiddle  , Forward_Backward);		// Move Right 		Rear/Middle  Leg backward and wait until done
					twitch(RightMiddle , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					twitch(RightRear   , Forward_Backward, true);		// Move Right 		Rear/Middle  Leg backward and wait until done
				}
				else if( i == 1)
				{
					twitch(LeftFront   , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					twitch(LeftRear    , Forward_Backward);		// Move Right 		Rear/Middle  Leg backward and wait until done
					twitch(RightMiddle , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					twitch(RightFront  , Forward_Backward, true);		// Move Right 		Rear/Middle  Leg backward and wait until done
				}
				else if( i == 2)
				{
					twitch(LeftRear   , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					twitch(LeftMiddle  , Forward_Backward);		// Move Right 		Rear/Middle  Leg backward and wait until done
					twitch(RightFront  , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					twitch(RightRear   , Forward_Backward, true);		// Move Right 		Rear/Middle  Leg backward and wait until done
				}
				// Down
				if( i == 0 )
				{
					write_ref((RightFront )*3   + Up_Down);			// Land Right 		Front/Middle Leg
					write_ref((LeftRear	  )*3   + Up_Down);		// Land Left 		Middle/Rear Leg and wait until done
					write_ref((RightMiddle)*3   + Forward_Backward);			// Land Right 		Front/Middle Leg
					write_ref((LeftFront  )*3   + Forward_Backward,true);		// Land Left 		Middle/Rear Leg and wait until done
				}
				else if( i == 1)
				{	
					write_ref((RightRear  )*3   + Up_Down);			// Land Right 		Front/Middle Leg
					write_ref((LeftMiddle )*3   + Up_Down);		// Land Left 		Middle/Rear Leg and wait until done
					write_ref((RightFront )*3   + Forward_Backward);			// Land Right 		Front/Middle Leg
					write_ref((LeftRear	  )*3   + Forward_Backward,true);		// Land Left 		Middle/Rear Leg and wait until done
					
				}
				else if( i == 2)
				{
					write_ref((RightMiddle)*3   + Up_Down);			// Land Right 		Front/Middle Leg
					write_ref((LeftFront  )*3   + Up_Down);		// Land Left 		Middle/Rear Leg and wait until done
					write_ref((RightRear  )*3   + Forward_Backward);			// Land Right 		Front/Middle Leg
					write_ref((LeftMiddle )*3   + Forward_Backward,true);		// Land Left 		Middle/Rear Leg and wait until done
					
				}
			}
		break;

		case 2:
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				twitch(LeftFront + i, Up_Down,true);						// Rise Right/Left 	Rear/Front   Leg
				
				// Rotate right
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,-zRotation);
				twitch(LeftFront  + i, Forward_Backward, true);		// Move Left 		Middle/Rear   Leg forward and wait until done
				
				// Down
				write_ref((LeftFront + i)*3   + Up_Down, true);		// Land Left 		Middle/Rear Leg and wait until done

			}
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				twitch(RightFront + i, Up_Down,true);						// Rise Right/Left 	Rear/Front   Leg
				
				// Rotate right
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,-zRotation);
				twitch(RightFront  + i, Forward_Backward, true);		// Move Left 		Middle/Rear   Leg forward and wait until done
				
				// Down
				write_ref((RightFront + i)*3   + Up_Down, true);		// Land Left 		Middle/Rear Leg and wait until done
				
			}
			for(int servoNum = 0; servoNum <= 15;)
			{
				write_ref(servoNum);
				servoNum +=3;
			}
		break;
	}
	
}


void walkingPattern::left(int vel,int mode){  
	velocity = vel;
	
	
	switch(mode)
	{
		case 0:
			for(byte i=0; i<2; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				twitch(RightFront   + i, Up_Down);						// Rise Right 		Front/Middle Leg
				twitch(RightRear    + i, Up_Down);						// Rise Right/Left 	Rear/Front   Leg
				twitch(LeftMiddle 	+ i, Up_Down, true);				// Rise Left 		Middle/Rear  Leg and wait until done
				
				// Rotate left
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,zRotation);
				twitch(RightFront   + i, Forward_Backward);         	// Rotate Left  		Front/Middle  Leg Left
				twitch(RightRear    + i, Forward_Backward);				// Rotate Left/Right	Rear/Front    Leg Left
				twitch(LeftMiddle	+ i, Forward_Backward, true);		// Rotate Right 		Middle/Rear   Leg Left and wait until done
					
				// Rotate right
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,-zRotation);
				twitch(RightMiddle - i, Forward_Backward);				// Rotate Right			Middle/Front Leg Right
				twitch(LeftFront   - i, Forward_Backward);				// Rotate Left/Right  	Front/Rear   Leg Right
				twitch(LeftRear    - i, Forward_Backward, true);		// Rotate Left	 		Rear/Middle  Leg Right and wait until done
			
				// Down
				write_ref((RightFront   + i)*3   + Up_Down);			// Land Right 		Front/Middle Leg
				write_ref((RightRear    + i)*3   + Up_Down);			// Land Right/Left  Rear/Front   Leg
				write_ref((LeftMiddle	+ i)*3   + Up_Down, true);		// Land Left 		Middle/Rear Leg and wait until done
			}
		break;
		
		case 1:
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				if( i == 0 )
				{
					twitch(RightFront  , Up_Down);						// Rise Right 		Front/Middle Leg
					twitch(LeftRear    , Up_Down,true);					// Rise Right 		Front/Middle Leg
				}
				else if( i == 1)
				{
					twitch(RightRear   , Up_Down);		
					twitch(LeftMiddle  , Up_Down,true);
				}
				else if( i == 2)
				{
					twitch(RightMiddle , Up_Down);	
					twitch(LeftFront   , Up_Down,true);							
				}
		
				// Rotate left
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,zRotation);
				if( i == 0 )
				{
					twitch(RightFront  , Forward_Backward);						// Rise Right 		Front/Middle Leg
					twitch(LeftRear    , Forward_Backward,true);					// Rise Right 		Front/Middle Leg
				}
				else if( i == 1)
				{
					twitch(RightRear   , Forward_Backward);		
					twitch(LeftMiddle  , Forward_Backward,true);
				}
				else if( i == 2)
				{
					twitch(RightMiddle , Forward_Backward);	
					twitch(LeftFront   , Forward_Backward,true);							
				}
				
				// Rotate right
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,-zRotation);
				if( i == 0)
				{
					twitch(LeftFront   , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					twitch(LeftMiddle  , Forward_Backward);		// Move Right 		Rear/Middle  Leg backward and wait until done
					twitch(RightMiddle , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					twitch(RightRear   , Forward_Backward, true);		// Move Right 		Rear/Middle  Leg backward and wait until done
				}
				else if( i == 1)
				{
					twitch(LeftFront   , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					twitch(LeftRear    , Forward_Backward);		// Move Right 		Rear/Middle  Leg backward and wait until done
					twitch(RightMiddle , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					twitch(RightFront  , Forward_Backward, true);		// Move Right 		Rear/Middle  Leg backward and wait until done
				}
				else if( i == 2)
				{
					twitch(LeftRear   , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					twitch(LeftMiddle  , Forward_Backward);		// Move Right 		Rear/Middle  Leg backward and wait until done
					twitch(RightFront  , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					twitch(RightRear   , Forward_Backward, true);		// Move Right 		Rear/Middle  Leg backward and wait until done
				}
				// Down
				if( i == 0 )
				{
					write_ref((RightFront )*3   + Up_Down);			// Land Right 		Front/Middle Leg
					write_ref((LeftRear	  )*3   + Up_Down);		// Land Left 		Middle/Rear Leg and wait until done
					write_ref((RightMiddle)*3   + Forward_Backward);			// Land Right 		Front/Middle Leg
					write_ref((LeftFront  )*3   + Forward_Backward,true);		// Land Left 		Middle/Rear Leg and wait until done
				}
				else if( i == 1)
				{	
					write_ref((RightRear  )*3   + Up_Down);			// Land Right 		Front/Middle Leg
					write_ref((LeftMiddle )*3   + Up_Down);		// Land Left 		Middle/Rear Leg and wait until done
					write_ref((RightFront )*3   + Forward_Backward);			// Land Right 		Front/Middle Leg
					write_ref((LeftRear	  )*3   + Forward_Backward,true);		// Land Left 		Middle/Rear Leg and wait until done
					
				}
				else if( i == 2)
				{
					write_ref((RightMiddle)*3   + Up_Down);			// Land Right 		Front/Middle Leg
					write_ref((LeftFront  )*3   + Up_Down);		// Land Left 		Middle/Rear Leg and wait until done
					write_ref((RightRear  )*3   + Forward_Backward);			// Land Right 		Front/Middle Leg
					write_ref((LeftMiddle )*3   + Forward_Backward,true);		// Land Left 		Middle/Rear Leg and wait until done
					
				}
			}
		break;

		case 2:
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				twitch(LeftFront + i, Up_Down,true);						// Rise Right/Left 	Rear/Front   Leg
				
				// Rotate left
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,zRotation);
				twitch(LeftFront  + i, Forward_Backward, true);		// Move Left 		Middle/Rear   Leg forward and wait until done
				
				// Down
				write_ref((LeftFront + i)*3   + Up_Down, true);		// Land Left 		Middle/Rear Leg and wait until done

			}
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				twitch(RightFront + i, Up_Down,true);						// Rise Right/Left 	Rear/Front   Leg
				
				// Rotate left
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,zRotation);
				twitch(RightFront  + i, Forward_Backward, true);		// Move Left 		Middle/Rear   Leg forward and wait until done
				
				// Down
				write_ref((RightFront + i)*3   + Up_Down, true);		// Land Left 		Middle/Rear Leg and wait until done
				
			}
			for(int servoNum = 0; servoNum <= 15;)
			{
				write_ref(servoNum);
				servoNum +=3;
			}
		break;
	}
}

void walkingPattern::standUp(int val){
	velocity = val;
	for(int servoNum = 2; servoNum <= 17;)
	{
		write_ref(servoNum);									// Set angles for Tibia
		servoNum +=3;
	}
	// Set angles for Coxa
	for(int servoNum = 0; servoNum <= 15;)
	{
		write_ref(servoNum);									// Set angles for Coxa
		servoNum +=3;
	}
	// Set angles for Femmur
	for(int servoNum = 1; servoNum <= 16;)
	{
		write_ref(servoNum);									// Set angles for Femmur
		servoNum +=3;
	}
	
}

void walkingPattern::set_Down(int val)
{
	trans_rotat(val,0,0,55,0,0,0);
}

#include "WalkingPattern.h"
void walkingPattern::forward(int vel,int mode){  
	_zagHexa_.velocity = vel;
	switch(mode)
	{
		case 0:
			for(byte i=0; i<2;i++)
			{
				// Up 
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				_zagHexa_.twitch(RightRear  + i, Up_Down);						// Rise Right/Left 	Rear/Front   Leg
				_zagHexa_.twitch(RightFront + i, Up_Down);						// Rise Right 		Front/Middle Leg
				_zagHexa_.twitch(LeftMiddle + i, Up_Down, true);				// Rise Left 		Middle/Rear  Leg and wait until done
		
				// Forward
				_zagHexa_.clacHexaBodyIK(0,yShift/2,0,0,0,0);
				_zagHexa_.twitch(RightFront  + i, Forward_Backward);         	// Move Right  		Front/Middle  Leg forward
				_zagHexa_.twitch(RightRear   + i, Forward_Backward);				// Move Right/Left  Rear/Front    Leg forward
				_zagHexa_.twitch(LeftMiddle  + i, Forward_Backward, true);		// Move Left 		Middle/Rear   Leg forward and wait until done
			
				// Backward
				_zagHexa_.clacHexaBodyIK(0,-yShift,0,0,0,0);
				_zagHexa_.twitch(LeftFront		- i, Forward_Backward);			// Move Left 		Middle/Front Leg backward
				_zagHexa_.twitch(LeftRear		- i, Forward_Backward);			// Move Left/Left   Front/Rear   Leg backward
				_zagHexa_.twitch(RightMiddle	- i, Forward_Backward, true);		// Move Right 		Rear/Middle  Leg backward and wait until done
	
				// Down
				_zagHexa_.write_ref((RightFront + i)*3 	+ Up_Down);			// Land Right 		Front/Middle Leg
				_zagHexa_.write_ref((RightRear  + i)*3 	+ Up_Down);			// Land Right/Left  Rear/Front   Leg
				_zagHexa_.write_ref((LeftMiddle	+ i)*3	+ Up_Down, true);		// Land Left 		Middle/Rear  Leg and wait until done
			}
		break;
		
		case 1:
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				if( i == 0 )
				{
					_zagHexa_.twitch(RightFront  , Up_Down);						// Rise Right	Front Leg
					_zagHexa_.twitch(LeftRear    , Up_Down,true);					// Rise Left	Rear  Leg and wait until done
				}
				else if( i == 2)
				{
					_zagHexa_.twitch(RightMiddle , Up_Down);						// Rise Right	Middle Leg
					_zagHexa_.twitch(LeftFront   , Up_Down,true);					// Rise Left	Front  Leg and wait until done					
				}
				else if( i == 1)
				{
					_zagHexa_.twitch(RightRear   , Up_Down);						// Rise Right	Rear   Leg
					_zagHexa_.twitch(LeftMiddle  , Up_Down,true);					// Rise Left	Middle Leg and wait until done
				}
				else
				{
					/* Do nothing */
				}
			
				// Forward
				_zagHexa_.clacHexaBodyIK(0,yShift/2,0,0,0,0);
				if( i == 0 )
				{
					_zagHexa_.twitch(RightFront  , Forward_Backward);				// Move Right Front Leg forward
					_zagHexa_.twitch(LeftRear    , Forward_Backward,true);		// Move Left  Rear  Leg forward and wait until done
				}
				else if( i == 2)
				{
					_zagHexa_.twitch(RightMiddle , Forward_Backward);				// Move Right Middle Leg forward
					_zagHexa_.twitch(LeftFront   , Forward_Backward,true);		// Move Left  Front  Leg forward and wait until done			
				}
				else if( i == 1)
				{
					_zagHexa_.twitch(RightRear   , Forward_Backward);				// Move Right Rear   Leg forward
					_zagHexa_.twitch(LeftMiddle  , Forward_Backward,true);		// Move Left  Middle Leg forward and wait until done
				
				}
				else
				{
					/* Do nothing */
				}
				
				// Backward
				_zagHexa_.clacHexaBodyIK(0,-yShift,0,0,0,0);
				if( i == 0)
				{
					_zagHexa_.twitch(LeftFront   , Forward_Backward);				// Move Left  Front   Leg backward
					_zagHexa_.twitch(LeftMiddle  , Forward_Backward);				// Move Left  Middle  Leg backward
					_zagHexa_.twitch(RightMiddle , Forward_Backward);				// Move Right Middle  Leg backward
					_zagHexa_.twitch(RightRear   , Forward_Backward, true);		// Move Right Rear    Leg backward and wait until done
				}
				else if( i == 2)
				{
					_zagHexa_.twitch(LeftMiddle  , Forward_Backward);				// Move Left  Middle Leg backward
					_zagHexa_.twitch(LeftRear    , Forward_Backward);				// Move Left  Rear   Leg backward
					_zagHexa_.twitch(RightRear   , Forward_Backward);				// Move Right Rear   Leg backward
					_zagHexa_.twitch(RightFront  , Forward_Backward, true);		// Move Right Front  Leg backward and wait until done
				}
				else if( i == 1)
				{
					_zagHexa_.twitch(LeftRear    , Forward_Backward);				// Move Left  Rear    Leg backward
					_zagHexa_.twitch(LeftFront   , Forward_Backward);				// Move Left  Front   Leg backward 
					_zagHexa_.twitch(RightFront  , Forward_Backward);				// Move Right Front   Leg backward
					_zagHexa_.twitch(RightMiddle , Forward_Backward, true);		// Move Right Middle  Leg backward and wait until done
				
				}
				else
				{
					/* Do nothing */
				}
				
				// Down and move back
				if( i == 0 )
				{
					_zagHexa_.write_ref((RightFront )*3   + Up_Down);					// Land Right Front  Leg
					_zagHexa_.write_ref((LeftRear	  )*3   + Up_Down);					// Land Left  Rear   Leg 
					_zagHexa_.write_ref((RightRear  )*3   + Forward_Backward);		// Move Right Rear   Leg backward
					_zagHexa_.write_ref((LeftMiddle )*3   + Forward_Backward,true);	// Move Left  Middle Leg backward and wait until done
					
				}
				else if( i == 2)
				{	
					_zagHexa_.write_ref((RightMiddle)*3   + Up_Down);					// Land Right Middle Leg
					_zagHexa_.write_ref((LeftFront  )*3   + Up_Down);					// Land Left  Front  Leg 
					_zagHexa_.write_ref((RightFront )*3   + Forward_Backward);		// Move Right Front  Leg backward
					_zagHexa_.write_ref((LeftRear   )*3   + Forward_Backward,true);	// Move Left  Rear   Leg backward and wait until done
				}
				else if( i == 1)
				{
					_zagHexa_.write_ref((RightRear  )*3   + Up_Down);					// Land Right 		Rear   Leg
					_zagHexa_.write_ref((LeftMiddle )*3   + Up_Down);					// Land Left 		Middle Leg 
					_zagHexa_.write_ref((RightMiddle)*3   + Forward_Backward);		// Move Right 		Middle Leg backward
					_zagHexa_.write_ref((LeftFront  )*3   + Forward_Backward,true);	// Move Left 		Front  Leg backward and wait until done
					
				}
				else
				{
					/* Do nothing */
				}
			}/*
			for(int servoNum = 0; servoNum <= 15;)
			{
				_zagHexa_.write_ref(servoNum);
				servoNum +=3;
			}*/
		break;

		case 2:
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				_zagHexa_.twitch(LeftFront + i, Up_Down,true);					// Rise Legs From LeftFront to LeftRear
				
				// Forward
				_zagHexa_.clacHexaBodyIK(0,yShift,0,0,0,0);
				_zagHexa_.twitch(LeftFront  + i, Forward_Backward, true);			// Move Legs From LeftFront to LeftRear forward 
				
				// Down
				_zagHexa_.write_ref((LeftFront + i)*3   + Up_Down, true);			// Land Legs From LeftFront to LeftRear 

			}
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				_zagHexa_.twitch(RightFront + i, Up_Down,true);					// Rise Legs From RightFront to RightRear 
				
				// Forward
				_zagHexa_.clacHexaBodyIK(0,yShift,0,0,0,0);
				_zagHexa_.twitch(RightFront  + i, Forward_Backward, true);		// Move Legs From RightFront to RightRar forward 
				
				// Down
				_zagHexa_.write_ref((RightFront + i)*3   + Up_Down, true);		// Land Legs From RightFront to RightRear 
				
			}
			for(int servoNum = 0; servoNum <= 15;)
			{
				_zagHexa_.write_ref(servoNum);									// Move all Coxa to the zero position
				servoNum +=3;
			}
		break;
			
			
	}
}	
void walkingPattern::backward(int vel, int mode){  
	_zagHexa_.velocity = vel;
	
	switch(mode)
	{
		case 0:
			for(int i=0; i <2; i++)
			{
				// Up 
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				_zagHexa_.twitch(RightFront   + i, Up_Down);						// Rise Right 		Front/Middle Leg
				_zagHexa_.twitch(RightRear    + i, Up_Down);						// Rise Right/Left 	Rear/Front   Leg
				_zagHexa_.twitch(LeftMiddle 	+ i, Up_Down, true);				// Rise Left 		Middle/Rear  Leg and wait until done
				
				// Backward
				_zagHexa_.clacHexaBodyIK(0,-yShift/2,0,0,0,0);
				_zagHexa_.twitch(RightFront   + i, Forward_Backward);          	// Move Right  		Front/Middle  Leg backward
				_zagHexa_.twitch(RightRear    + i, Forward_Backward);				// Move Right/Left  Rear/Front    Leg backward
				_zagHexa_.twitch(LeftMiddle   + i, Forward_Backward, true);		// Move Right 		Middle/Rear   Leg backward and wait until done
				
				// Forward
				_zagHexa_.clacHexaBodyIK(0,yShift,0,0,0,0);
				_zagHexa_.twitch(LeftFront  	 - i, Forward_Backward);			// Move Left 		Middle/Front Leg forward
				_zagHexa_.twitch(LeftRear    	 - i, Forward_Backward);			// Move Left/Left   Front/Rear   Leg forward
				_zagHexa_.twitch(RightMiddle   - i, Forward_Backward, true);		// Move Right 		Rear/Middle  Leg forward and wait until done
			
				// Down
				_zagHexa_.write_ref((RightFront   + i)*3   + Up_Down);			// Land Right 		Front/Middle Leg
				_zagHexa_.write_ref((RightRear    + i)*3   + Up_Down);			// Land Right/Left  Rear/Front   Leg
				_zagHexa_.write_ref((LeftMiddle	+ i)*3   + Up_Down, true);		// Land Left 		Middle/Rear Leg and wait until done
			
			}
		break;
		
		case 1:
		for(byte i=0; i<3; i++)
			{
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				if( i == 0 )
				{
					_zagHexa_.twitch(RightFront  , Up_Down);						// Rise Right	Front Leg
					_zagHexa_.twitch(LeftRear    , Up_Down,true);					// Rise Left	Rear  Leg and wait until done
				}
				else if( i == 2)
				{
					_zagHexa_.twitch(RightRear   , Up_Down);						// Rise Right	Rear   Leg
					_zagHexa_.twitch(LeftMiddle  , Up_Down,true);					// Rise Left	Middle Leg and wait until done
				}
				else if( i == 1)
				{
					_zagHexa_.twitch(RightMiddle , Up_Down);						// Rise Right	Middle Leg
					_zagHexa_.twitch(LeftFront   , Up_Down,true);					// Rise Left	Front  Leg and wait until done
				}
				else
				{
					/* Do nothing */
				}
		
				// Backward
				_zagHexa_.clacHexaBodyIK(0,-yShift/2,0,0,0,0);
				if( i == 0 )
				{
					_zagHexa_.twitch(RightFront  , Forward_Backward);				// Move Right  Front  Leg backward
					_zagHexa_.twitch(LeftRear    , Forward_Backward,true);		// Move Left   Rear   Leg backward and wait until done
				}
				else if( i == 2)
				{
					_zagHexa_.twitch(RightRear   , Forward_Backward);				// Move Right  Rear   Leg backward
					_zagHexa_.twitch(LeftMiddle  , Forward_Backward,true);		// Move Left   Middle Leg backward and wait until done
				}
				else if( i == 1)
				{
					_zagHexa_.twitch(RightMiddle , Forward_Backward);				// Move Right  Middle Leg backward
					_zagHexa_.twitch(LeftFront   , Forward_Backward,true);		// Move Left   Front  Leg backward and wait until done
				}
				else
				{
					/* Do nothing */
				}
				
				// Forward
				_zagHexa_.clacHexaBodyIK(0,yShift,0,0,0,0);
				if( i == 0)
				{
					_zagHexa_.twitch(LeftFront   , Forward_Backward);				// Move Left  Front  Leg forward
					_zagHexa_.twitch(LeftMiddle  , Forward_Backward);				// Move Left  Middle Leg forward
					_zagHexa_.twitch(RightMiddle , Forward_Backward);				// Move Right Middle Leg forward
					_zagHexa_.twitch(RightRear   , Forward_Backward, true);		// Move Right Rear   Leg forward and wait until done
				}
				else if( i == 2)
				{
					_zagHexa_.twitch(LeftFront   , Forward_Backward);				// Move Left  Front  Leg forward
					_zagHexa_.twitch(LeftRear    , Forward_Backward);				// Move Left  Rear   Leg forward
					_zagHexa_.twitch(RightMiddle , Forward_Backward);				// Move Right Middle Leg forward
					_zagHexa_.twitch(RightFront  , Forward_Backward, true);		// Move Right Front  Leg forward and wait until done
				}
				else if( i == 1)
				{
					_zagHexa_.twitch(LeftRear    , Forward_Backward);				// Move Left  Rear   Leg forward
					_zagHexa_.twitch(LeftMiddle  , Forward_Backward);				// Move Left  Middle Leg forward
					_zagHexa_.twitch(RightFront  , Forward_Backward);				// Move Right Front  Leg forward
					_zagHexa_.twitch(RightRear   , Forward_Backward, true);		// Move Right Rear   Leg forward and wait until done
				}
				else
				{
					/* Do nothing */
				}
				// Down
				if( i == 0 )
				{
					_zagHexa_.write_ref((RightFront )*3   + Up_Down);					// Land Right Front  Leg
					_zagHexa_.write_ref((LeftRear	  )*3   + Up_Down);					// Land Left  Rear   Leg
					_zagHexa_.write_ref((RightMiddle)*3   + Forward_Backward);		// Move Right Middle Leg forward
					_zagHexa_.write_ref((LeftFront  )*3   + Forward_Backward,true);	// Move Left  Front  Leg forward and wait until done
				}
				else if( i == 1)
				{
					_zagHexa_.write_ref((RightMiddle)*3   + Up_Down);					// Land Right Middle Leg
					_zagHexa_.write_ref((LeftFront  )*3   + Up_Down);					// Land Left  Front  Leg
					_zagHexa_.write_ref((RightFront )*3   + Forward_Backward);		// Move Right Front  Leg forward
					_zagHexa_.write_ref((LeftRear   )*3   + Forward_Backward,true);	// Move Left  Rear   Leg forward and wait until done
				 
				}
				else if( i == 2)
				{	
					_zagHexa_.write_ref((RightRear  )*3   + Up_Down);					// Land Right Rear   Leg
					_zagHexa_.write_ref((LeftMiddle )*3   + Up_Down);					// Land Left  Middle Leg
					_zagHexa_.write_ref((RightMiddle)*3   + Forward_Backward);		// Move Right Middle Leg forward
					_zagHexa_.write_ref((LeftFront  )*3   + Forward_Backward,true);	// Move Left  Front  Leg forward and wait until done
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
				_zagHexa_.twitch(LeftFront + i, Up_Down,true);					// Rise Legs From LeftFront to LeftRear
				
				// Backward
				_zagHexa_.clacHexaBodyIK(0,-yShift,0,0,0,0);
				_zagHexa_.twitch(LeftFront  + i, Forward_Backward, true);			// Move Legs From LeftFront to LeftRear backward
				
				// Down
				_zagHexa_.write_ref((LeftFront + i)*3   + Up_Down, true);			// Land Legs From LeftFront to LeftRear

			}
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				_zagHexa_.twitch(RightFront + i, Up_Down,true);					// Rise Legs From RightFront to RightRear 
				
				// Backward
				_zagHexa_.clacHexaBodyIK(0,-yShift,0,0,0,0);
				_zagHexa_.twitch(RightFront  + i, Forward_Backward, true);		// Move Legs From RightFront to RightRear backward
				
				// Down
				_zagHexa_.write_ref((RightFront + i)*3   + Up_Down, true);		// Land Legs From RightFront to RightRear 
				
			}
			for(int servoNum = 0; servoNum <= 15;)
			{
				_zagHexa_.write_ref(servoNum);									// Move all Coxa to the zero position
				servoNum +=3;
			}
		break;
	}
}
void walkingPattern::right(int vel,int mode){  
	_zagHexa_.velocity = vel;
	switch(mode)
	{
		case 0:
			for(byte i=0; i<2; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				_zagHexa_.twitch(RightFront   + i, Up_Down);						// Rise Right 		Front/Middle Leg
				_zagHexa_.twitch(RightRear    + i, Up_Down);						// Rise Right/Left 	Rear/Front   Leg
				_zagHexa_.twitch(LeftMiddle 	+ i, Up_Down, true);				// Rise Left 		Middle/Rear  Leg and wait until done
				
				// Rotate right
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,-zRotation);
				_zagHexa_.twitch(RightFront   + i, Forward_Backward);         	// Rotate Left  		Front/Middle  Leg Right
				_zagHexa_.twitch(RightRear    + i, Forward_Backward);				// Rotate Left/Right	Rear/Front    Leg Right
				_zagHexa_.twitch(LeftMiddle	+ i, Forward_Backward, true);		// Rotate Right 		Middle/Rear   Leg Right and wait until done
					
				// Rotate left
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,zRotation);
				_zagHexa_.twitch(RightMiddle - i, Forward_Backward);				// Rotate Right			Middle/Front Leg Left
				_zagHexa_.twitch(LeftFront   - i, Forward_Backward);				// Rotate Left/Right  	Front/Rear   Leg Left
				_zagHexa_.twitch(LeftRear    - i, Forward_Backward, true);		// Rotate Left	 		Rear/Middle  Leg Left and wait until done
			
				// Down
				_zagHexa_.write_ref((RightFront   + i)*3   + Up_Down);			// Land Right 		Front/Middle Leg
				_zagHexa_.write_ref((RightRear    + i)*3   + Up_Down);			// Land Right/Left  Rear/Front   Leg
				_zagHexa_.write_ref((LeftMiddle	+ i)*3   + Up_Down, true);		// Land Left 		Middle/Rear Leg and wait until done
			
			}
		break;
		
		case 1:
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				if( i == 0 )
				{
					_zagHexa_.twitch(RightFront  , Up_Down);						// Rise Right 		Front/Middle Leg
					_zagHexa_.twitch(LeftRear    , Up_Down,true);					// Rise Right 		Front/Middle Leg
				}
				else if( i == 1)
				{
					_zagHexa_.twitch(RightRear   , Up_Down);		
					_zagHexa_.twitch(LeftMiddle  , Up_Down,true);
				}
				else if( i == 2)
				{
					_zagHexa_.twitch(RightMiddle , Up_Down);	
					_zagHexa_.twitch(LeftFront   , Up_Down,true);							
				}
		
				// Rotate right
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,-zRotation);
				if( i == 0 )
				{
					_zagHexa_.twitch(RightFront  , Forward_Backward);						// Rise Right 		Front/Middle Leg
					_zagHexa_.twitch(LeftRear    , Forward_Backward,true);					// Rise Right 		Front/Middle Leg
				}
				else if( i == 1)
				{
					_zagHexa_.twitch(RightRear   , Forward_Backward);		
					_zagHexa_.twitch(LeftMiddle  , Forward_Backward,true);
				}
				else if( i == 2)
				{
					_zagHexa_.twitch(RightMiddle , Forward_Backward);	
					_zagHexa_.twitch(LeftFront   , Forward_Backward,true);							
				}
				
				// Rotate left
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,zRotation);
				if( i == 0)
				{
					_zagHexa_.twitch(LeftFront   , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					_zagHexa_.twitch(LeftMiddle  , Forward_Backward);		// Move Right 		Rear/Middle  Leg backward and wait until done
					_zagHexa_.twitch(RightMiddle , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					_zagHexa_.twitch(RightRear   , Forward_Backward, true);		// Move Right 		Rear/Middle  Leg backward and wait until done
				}
				else if( i == 1)
				{
					_zagHexa_.twitch(LeftFront   , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					_zagHexa_.twitch(LeftRear    , Forward_Backward);		// Move Right 		Rear/Middle  Leg backward and wait until done
					_zagHexa_.twitch(RightMiddle , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					_zagHexa_.twitch(RightFront  , Forward_Backward, true);		// Move Right 		Rear/Middle  Leg backward and wait until done
				}
				else if( i == 2)
				{
					_zagHexa_.twitch(LeftRear   , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					_zagHexa_.twitch(LeftMiddle  , Forward_Backward);		// Move Right 		Rear/Middle  Leg backward and wait until done
					_zagHexa_.twitch(RightFront  , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					_zagHexa_.twitch(RightRear   , Forward_Backward, true);		// Move Right 		Rear/Middle  Leg backward and wait until done
				}
				// Down
				if( i == 0 )
				{
					_zagHexa_.write_ref((RightFront )*3   + Up_Down);			// Land Right 		Front/Middle Leg
					_zagHexa_.write_ref((LeftRear	  )*3   + Up_Down);		// Land Left 		Middle/Rear Leg and wait until done
					_zagHexa_.write_ref((RightMiddle)*3   + Forward_Backward);			// Land Right 		Front/Middle Leg
					_zagHexa_.write_ref((LeftFront  )*3   + Forward_Backward,true);		// Land Left 		Middle/Rear Leg and wait until done
				}
				else if( i == 1)
				{	
					_zagHexa_.write_ref((RightRear  )*3   + Up_Down);			// Land Right 		Front/Middle Leg
					_zagHexa_.write_ref((LeftMiddle )*3   + Up_Down);		// Land Left 		Middle/Rear Leg and wait until done
					_zagHexa_.write_ref((RightFront )*3   + Forward_Backward);			// Land Right 		Front/Middle Leg
					_zagHexa_.write_ref((LeftRear	  )*3   + Forward_Backward,true);		// Land Left 		Middle/Rear Leg and wait until done
					
				}
				else if( i == 2)
				{
					_zagHexa_.write_ref((RightMiddle)*3   + Up_Down);			// Land Right 		Front/Middle Leg
					_zagHexa_.write_ref((LeftFront  )*3   + Up_Down);		// Land Left 		Middle/Rear Leg and wait until done
					_zagHexa_.write_ref((RightRear  )*3   + Forward_Backward);			// Land Right 		Front/Middle Leg
					_zagHexa_.write_ref((LeftMiddle )*3   + Forward_Backward,true);		// Land Left 		Middle/Rear Leg and wait until done
					
				}
			}
		break;

		case 2:
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				_zagHexa_.twitch(LeftFront + i, Up_Down,true);						// Rise Right/Left 	Rear/Front   Leg
				
				// Rotate right
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,-zRotation);
				_zagHexa_.twitch(LeftFront  + i, Forward_Backward, true);		// Move Left 		Middle/Rear   Leg forward and wait until done
				
				// Down
				_zagHexa_.write_ref((LeftFront + i)*3   + Up_Down, true);		// Land Left 		Middle/Rear Leg and wait until done

			}
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				_zagHexa_.twitch(RightFront + i, Up_Down,true);						// Rise Right/Left 	Rear/Front   Leg
				
				// Rotate right
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,-zRotation);
				_zagHexa_.twitch(RightFront  + i, Forward_Backward, true);		// Move Left 		Middle/Rear   Leg forward and wait until done
				
				// Down
				_zagHexa_.write_ref((RightFront + i)*3   + Up_Down, true);		// Land Left 		Middle/Rear Leg and wait until done
				
			}
			for(int servoNum = 0; servoNum <= 15;)
			{
				_zagHexa_.write_ref(servoNum);
				servoNum +=3;
			}
		break;
	}
	
}
void walkingPattern::left(int vel,int mode){  
	_zagHexa_.velocity = vel;
	switch(mode)
	{
		case 0:
			for(byte i=0; i<2; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				_zagHexa_.twitch(RightFront   + i, Up_Down);						// Rise Right 		Front/Middle Leg
				_zagHexa_.twitch(RightRear    + i, Up_Down);						// Rise Right/Left 	Rear/Front   Leg
				_zagHexa_.twitch(LeftMiddle 	+ i, Up_Down, true);				// Rise Left 		Middle/Rear  Leg and wait until done
				
				// Rotate left
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,zRotation);
				_zagHexa_.twitch(RightFront   + i, Forward_Backward);         	// Rotate Left  		Front/Middle  Leg Left
				_zagHexa_.twitch(RightRear    + i, Forward_Backward);				// Rotate Left/Right	Rear/Front    Leg Left
				_zagHexa_.twitch(LeftMiddle	+ i, Forward_Backward, true);		// Rotate Right 		Middle/Rear   Leg Left and wait until done
					
				// Rotate right
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,-zRotation);
				_zagHexa_.twitch(RightMiddle - i, Forward_Backward);				// Rotate Right			Middle/Front Leg Right
				_zagHexa_.twitch(LeftFront   - i, Forward_Backward);				// Rotate Left/Right  	Front/Rear   Leg Right
				_zagHexa_.twitch(LeftRear    - i, Forward_Backward, true);		// Rotate Left	 		Rear/Middle  Leg Right and wait until done
			
				// Down
				_zagHexa_.write_ref((RightFront   + i)*3   + Up_Down);			// Land Right 		Front/Middle Leg
				_zagHexa_.write_ref((RightRear    + i)*3   + Up_Down);			// Land Right/Left  Rear/Front   Leg
				_zagHexa_.write_ref((LeftMiddle	+ i)*3   + Up_Down, true);		// Land Left 		Middle/Rear Leg and wait until done
			}
		break;
		
		case 1:
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				if( i == 0 )
				{
					_zagHexa_.twitch(RightFront  , Up_Down);						// Rise Right 		Front/Middle Leg
					_zagHexa_.twitch(LeftRear    , Up_Down,true);					// Rise Right 		Front/Middle Leg
				}
				else if( i == 1)
				{
					_zagHexa_.twitch(RightRear   , Up_Down);		
					_zagHexa_.twitch(LeftMiddle  , Up_Down,true);
				}
				else if( i == 2)
				{
					_zagHexa_.twitch(RightMiddle , Up_Down);	
					_zagHexa_.twitch(LeftFront   , Up_Down,true);							
				}
		
				// Rotate left
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,zRotation);
				if( i == 0 )
				{
					_zagHexa_.twitch(RightFront  , Forward_Backward);						// Rise Right 		Front/Middle Leg
					_zagHexa_.twitch(LeftRear    , Forward_Backward,true);					// Rise Right 		Front/Middle Leg
				}
				else if( i == 1)
				{
					_zagHexa_.twitch(RightRear   , Forward_Backward);		
					_zagHexa_.twitch(LeftMiddle  , Forward_Backward,true);
				}
				else if( i == 2)
				{
					_zagHexa_.twitch(RightMiddle , Forward_Backward);	
					_zagHexa_.twitch(LeftFront   , Forward_Backward,true);							
				}
				
				// Rotate right
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,-zRotation);
				if( i == 0)
				{
					_zagHexa_.twitch(LeftFront   , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					_zagHexa_.twitch(LeftMiddle  , Forward_Backward);		// Move Right 		Rear/Middle  Leg backward and wait until done
					_zagHexa_.twitch(RightMiddle , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					_zagHexa_.twitch(RightRear   , Forward_Backward, true);		// Move Right 		Rear/Middle  Leg backward and wait until done
				}
				else if( i == 1)
				{
					_zagHexa_.twitch(LeftFront   , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					_zagHexa_.twitch(LeftRear    , Forward_Backward);		// Move Right 		Rear/Middle  Leg backward and wait until done
					_zagHexa_.twitch(RightMiddle , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					_zagHexa_.twitch(RightFront  , Forward_Backward, true);		// Move Right 		Rear/Middle  Leg backward and wait until done
				}
				else if( i == 2)
				{
					_zagHexa_.twitch(LeftRear   , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					_zagHexa_.twitch(LeftMiddle  , Forward_Backward);		// Move Right 		Rear/Middle  Leg backward and wait until done
					_zagHexa_.twitch(RightFront  , Forward_Backward);			// Move Left 		Middle/Front Leg backward
					_zagHexa_.twitch(RightRear   , Forward_Backward, true);		// Move Right 		Rear/Middle  Leg backward and wait until done
				}
				// Down
				if( i == 0 )
				{
					_zagHexa_.write_ref((RightFront )*3   + Up_Down);			// Land Right 		Front/Middle Leg
					_zagHexa_.write_ref((LeftRear	  )*3   + Up_Down);		// Land Left 		Middle/Rear Leg and wait until done
					_zagHexa_.write_ref((RightMiddle)*3   + Forward_Backward);			// Land Right 		Front/Middle Leg
					_zagHexa_.write_ref((LeftFront  )*3   + Forward_Backward,true);		// Land Left 		Middle/Rear Leg and wait until done
				}
				else if( i == 1)
				{	
					_zagHexa_.write_ref((RightRear  )*3   + Up_Down);			// Land Right 		Front/Middle Leg
					_zagHexa_.write_ref((LeftMiddle )*3   + Up_Down);		// Land Left 		Middle/Rear Leg and wait until done
					_zagHexa_.write_ref((RightFront )*3   + Forward_Backward);			// Land Right 		Front/Middle Leg
					_zagHexa_.write_ref((LeftRear	  )*3   + Forward_Backward,true);		// Land Left 		Middle/Rear Leg and wait until done
					
				}
				else if( i == 2)
				{
					_zagHexa_.write_ref((RightMiddle)*3   + Up_Down);			// Land Right 		Front/Middle Leg
					_zagHexa_.write_ref((LeftFront  )*3   + Up_Down);		// Land Left 		Middle/Rear Leg and wait until done
					_zagHexa_.write_ref((RightRear  )*3   + Forward_Backward);			// Land Right 		Front/Middle Leg
					_zagHexa_.write_ref((LeftMiddle )*3   + Forward_Backward,true);		// Land Left 		Middle/Rear Leg and wait until done
					
				}
			}
		break;

		case 2:
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				_zagHexa_.twitch(LeftFront + i, Up_Down,true);						// Rise Right/Left 	Rear/Front   Leg
				
				// Rotate left
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,zRotation);
				_zagHexa_.twitch(LeftFront  + i, Forward_Backward, true);		// Move Left 		Middle/Rear   Leg forward and wait until done
				
				// Down
				_zagHexa_.write_ref((LeftFront + i)*3   + Up_Down, true);		// Land Left 		Middle/Rear Leg and wait until done

			}
			for(byte i=0; i<3; i++)
			{
				// Up
				_zagHexa_.clacHexaBodyIK(0,0,zShift,0,0,0);
				_zagHexa_.twitch(RightFront + i, Up_Down,true);						// Rise Right/Left 	Rear/Front   Leg
				
				// Rotate left
				_zagHexa_.clacHexaBodyIK(0,0,0,0,0,zRotation);
				_zagHexa_.twitch(RightFront  + i, Forward_Backward, true);		// Move Left 		Middle/Rear   Leg forward and wait until done
				
				// Down
				_zagHexa_.write_ref((RightFront + i)*3   + Up_Down, true);		// Land Left 		Middle/Rear Leg and wait until done
				
			}
			for(int servoNum = 0; servoNum <= 15;)
			{
				_zagHexa_.write_ref(servoNum);
				servoNum +=3;
			}
		break;
	}
}
void walkingPattern::standUp(int val){
	_zagHexa_.velocity = val;
	for(int servoNum = 2; servoNum <= 17;)
	{
		_zagHexa_.write_ref(servoNum);									// Set angles for Tibia
		servoNum +=3;
	}
	// Set angles for Coxa
	for(int servoNum = 0; servoNum <= 15;)
	{
		_zagHexa_.write_ref(servoNum);									// Set angles for Coxa
		servoNum +=3;
	}
	// Set angles for Femmur
	for(int servoNum = 1; servoNum <= 16;)
	{
		_zagHexa_.write_ref(servoNum);									// Set angles for Femmur
		servoNum +=3;
	}
	
}
void walkingPattern::set_Down(int val)
{
	_zagHexa_.trans_rotat(val,0,0,55,0,0,0);
}
void walkingPattern::trans_rotat(int val,float PosX,float PosY, float PosZ,float RotX, float RotY, float RotZ)
{
	_zagHexa_.trans_rotat(val,PosX,PosY,PosZ,RotX,RotY,RotZ);
}
void walkingPattern::write_all_ref(int val = 255){
	_zagHexa_.trans_rotat(val,0,0,0,0,0,0);
}
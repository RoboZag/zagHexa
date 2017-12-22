#ifndef WalkingPattern_H_	
#define WalkingPattern_H_
#include <VarSpeedServo.h>
#include <BodyIK.h>
#define DEBUGE true	

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define RightFront	0
#define	RightMiddle 1
#define RightRear	2
#define LeftFront	3
#define LeftMiddle	4
#define LeftRear	5

#define RADIUS  60
#define UPDIST  30
#define ALPHA   60
 
class walkingPattern
{	
	
	BodyIk _zagHexa_;
	int    alpha;
	//float  xShift  = 10;
	float  yShift  = 45;	 
	float  zShift  = 30 ;  	
	float  zRotation  = 13;
	int    velocity;
	enum direc{Forward_Backward, Up_Down, In_Out};
public:
	VarSpeedServo   _Servo[18];
	void attch_servo();
	void write_all_ref(int val = 255);
	void write_ref(int, bool wait= false);
	void Tripod();
	void Wave();
	void Ripple();
	void initialize_servos(int);
	void twitch(int legNum, int offset, bool wait = false);
	void standUp(int);
	void set_Down(int);
	void forward(int,int);
	void backword(int,int);
	void right(int,int);
	void left(int,int);
	void trans_rotat(int,float,float,float,float,float,float);
};
#endif
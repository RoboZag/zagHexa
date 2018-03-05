#ifndef WalkingPattern_H_	
#define WalkingPattern_H_
#include <BodyIK.h>

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define DEBUGE		true	
#define RightFront	0
#define	RightMiddle 1
#define RightRear	2
#define LeftFront	3
#define LeftMiddle	4
#define LeftRear	5

class walkingPattern
{	
	BodyIk _zagHexa_;
	float  yShift  = 45;	 
	float  zShift  = 30 ;  	
	float  zRotation  = 13;
	enum direc{Forward_Backward, Up_Down, In_Out};
public:
	void forward(int,int);
	void backward(int,int);
	void right(int,int);
	void left(int,int);
	void standUp(int);
	void set_Down(int);
	void trans_rotat(int,float,float,float,float,float,float);
	void write_all_ref(int val = 255);
};
#endif
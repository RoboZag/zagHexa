#include <Walking_Patterns.h>

char data;
int mode = 1; //mode 1 for translation, mode 2 for tending, mode 3 for up and down

int main()
{
	start();
	Bluetoothe();

	while(1)
	{
	if (data == '1') 
	{
		if (mode == 1) 
			tripod_forward();
		if (mode == 2) 
			tilt_forward();
		if (mode == 3) 
			standup();
	}
	if (data == '2') 
	{
		if (mode == 1) 
			tripod_left();
		if (mode == 2) 
			tilt_left();
		if (mode == 3) 
			//do something 
	}
	if (data == '3') 
	{
		if (mode == 1)
			tripod_backward();
		if (mode == 2)
			tilt_backward();
		if (mode == 3)
			sitdown();
	}
	if (data == '4') 
	{
		if (mode == 1)
			tripod_right();
		if (mode == 2)
			tilt_right();
		if (mode == 3)
			// do something
	}
	if (data == 'x') 
	{
		// When x is call
	}
	if (data == 't') 
	{
		// When t is call
	}
	if (data == 'c') 
		mode++;
	if (data == 's') 
		reset_angles();
	if (mode > 3) 
		mode = 1;
}
	/*
while(1)
	{
	for(int i=150;i<700;i++)
		pwm.setPWM(0, 0, i);
	for(int i=600;i>0;i--)
		pwm.setPWM(0, 0, i);

	}*/
}

void start()
{
	// set the angles to the refrance 
	calibrate();
}

void Bluetoothe()
{
	// Setup Bluetoothe communcation

}
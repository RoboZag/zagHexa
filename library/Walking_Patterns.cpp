#include "Walking_Patterns.h"
#include "time.h"
	
Walking_Patterns::Walking_Patterns()
{
	pwm.begin();
	pwm.setPWMFreq(60);
	pwm1.begin();
	pwm1.setPWMFreq(60);
}

void Walking_Patterns::set_refAngle() {
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

void Walking_Patterns::init_oldAngle() {
	for (int i = 0; i < 18; i++) {
		oldAngle[i] = refAngle[i];
	}
}

void Walking_Patterns::reset_angles() {
	for (int servo_num = 0; servo_num < 18; servo_num++) {
		if (servo_num >= 0 && servo_num < 9) {
			pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num]));
		}
		else {
			pwm1.setPWM((servo_num - 9), 0, angle2pwm(refAngle[servo_num]));
		}
	}
}

void Walking_Patterns::calibrate() {
	set_refAngle();
	init_oldAngle();
	reset_angles();
	delay(2000);
}

void Walking_Patterns::twitch(int servo_num, int angle, int duration) {
	if (servo_num >= 0 && servo_num <= 8) {
		newAngle[servo_num] = refAngle[servo_num] - angle;
		if (newAngle[servo_num] >= oldAngle[servo_num]) {
			for (int i = oldAngle[servo_num]; i <= newAngle[servo_num]; i++) {
				pwm.setPWM(servo_num, 0, angle2pwm(i));
				delayMicroseconds(duration);
				
			}
		}
		else {
			for (int i = oldAngle[servo_num]; i >= newAngle[servo_num]; i--) {
				pwm.setPWM(servo_num, 0, angle2pwm(i));
				delayMicroseconds(duration);
				
			}
		}
	}
	else if (servo_num >= 9 && servo_num <= 17) {
		newAngle[servo_num] = refAngle[servo_num] + angle;
		if (newAngle[servo_num] >= oldAngle[servo_num]) {
			for (int i = oldAngle[servo_num]; i <= newAngle[servo_num]; i++) {
				pwm1.setPWM((servo_num - 9), 0, angle2pwm(i));
				delayMicroseconds(duration);
				
			}
		}
		else {
			for (int i = oldAngle[servo_num]; i >= newAngle[servo_num]; i--) {
				pwm1.setPWM((servo_num - 9), 0, angle2pwm(i));
				delayMicroseconds(duration);
				
			}
		}
	}
	oldAngle[servo_num] = newAngle[servo_num];
}

void Walking_Patterns::sitdown() {
	for (int servo_num = 0; servo_num < 18; servo_num++) {
		if (servo_num >= 0 && servo_num <= 8) {
			if ((servo_num % 3) == 0) {
				pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num]));
			}
			else {
				pwm.setPWM(servo_num, 0, angle2pwm((refAngle[servo_num] - 30)));
			}
		}
		if (servo_num >= 9 && servo_num <= 17) {
			if ((servo_num % 3) == 0) {
				pwm1.setPWM((servo_num - 9), 0, angle2pwm(refAngle[servo_num]));
			}
			else {
				pwm1.setPWM((servo_num - 9), 0, angle2pwm((refAngle[servo_num] + 30)));
			}
		}
	}
}

void Walking_Patterns::standup() {
	for (int servo_num = 0; servo_num < 18; servo_num++) {
		if (servo_num >= 0 && servo_num <= 8) {
			if ((servo_num % 3) == 0) {
				pwm.setPWM(servo_num, 0, angle2pwm(refAngle[servo_num]));
			}
			else {
				pwm.setPWM(servo_num, 0, angle2pwm((refAngle[servo_num] + 30)));
			}
		}
		if (servo_num >= 9 && servo_num <= 17) {
			if ((servo_num % 3) == 0) {
				pwm1.setPWM((servo_num - 9), 0, angle2pwm(refAngle[servo_num]));
			}
			else {
				pwm1.setPWM((servo_num - 9), 0, angle2pwm((refAngle[servo_num] - 30)));
			}
		}
	}
}

void Walking_Patterns::tripod_forward(int z_offset, int y_offset, int moveDelay, int stepDelay) {
	twitch(RightFrontLift, z_offset, moveDelay);   //raise right front leg 
	twitch(RightRearLift, z_offset, moveDelay);   //raise right rear leg
	twitch(LeftMiddleLift, z_offset, moveDelay);   //raise left middle leg
	delay(stepDelay);
	twitch(RightFrontRot, y_offset, moveDelay);   //move right front leg forward
	twitch(RightRearRot, y_offset, moveDelay);   //move right rear leg forward
	twitch(LeftMiddleRot, y_offset, moveDelay);   //move left middle leg forward
	twitch(LeftFrontRot, -(y_offset), moveDelay);   //move left front leg backward
	twitch(LeftRearRot, -(y_offset), moveDelay);   //move left rear leg backward
	twitch(RightMiddleRot, -(y_offset), moveDelay);   //move right middle leg backward
	delay(stepDelay);
	twitch(RightFrontLift, 0, moveDelay);   //lower right front leg
	twitch(RightFrontTibia, 0, moveDelay);   //fix right front Tibia
	twitch(RightRearLift, 0, moveDelay);   //lower right rear leg
	twitch(RightRearTibia, 0, moveDelay);   //fix right rear Tibia
	twitch(LeftMiddleLift, 0, moveDelay);   //lower left middle leg
	twitch(LeftMiddleTibia, 0, moveDelay);   //fix left middle Tibia  
	delay(stepDelay);
	twitch(LeftFrontLift, z_offset, moveDelay);   //raise left front leg 
	twitch(LeftRearLift, z_offset, moveDelay);   //raise left rear leg
	twitch(RightMiddleLift, z_offset, moveDelay);   //raise Right middle leg
	delay(stepDelay);
	twitch(LeftFrontRot, y_offset, moveDelay);   //move left front leg forward
	twitch(LeftRearRot, y_offset, moveDelay);   //move left rear leg forward
	twitch(RightMiddleRot, y_offset, moveDelay);   //move right middle leg forward
	twitch(RightFrontRot, -(y_offset), moveDelay);   //move right front leg backward
	twitch(RightRearRot, -(y_offset), moveDelay);   //move right rear leg backward
	twitch(LeftMiddleRot, -(y_offset), moveDelay);   //move left middle leg backward
	delay(stepDelay);
	twitch(LeftFrontLift, 0, moveDelay);   //lower left front leg
	twitch(LeftFrontTibia, 0, moveDelay);   //fix left front Tibia
	twitch(LeftRearLift, 0, moveDelay);   //lower left rear leg
	twitch(LeftRearTibia, 0, moveDelay);   //fix left rear Tibia
	twitch(RightMiddleLift, 0, moveDelay);   //lower right middle leg
	twitch(RightMiddleTibia, 0, moveDelay);   //fix right middle Tibia
	delay(stepDelay);
}

void Walking_Patterns::tripod_backward(int z_offset, int y_offset, int moveDelay, int stepDelay) {
	twitch(LeftRearLift, z_offset, moveDelay);  //raise right front leg 
	twitch(LeftFrontLift, z_offset, moveDelay);  //raise right rear leg
	twitch(RightMiddleLift, z_offset, moveDelay);  //raise left middle leg
	delay(stepDelay);
	twitch(LeftRearRot, -(y_offset), moveDelay);  //move right front leg forward
	twitch(LeftFrontRot, -(y_offset), moveDelay);  //move right rear leg forward
	twitch(RightMiddleRot, -(y_offset), moveDelay);  //move left middle leg forward
	twitch(RightRearRot, y_offset, moveDelay);  //move left front leg backward
	twitch(RightFrontRot, y_offset, moveDelay);  //move left rear leg backward
	twitch(LeftMiddleRot, y_offset, moveDelay);  //move right middle leg backward
	delay(stepDelay);
	twitch(LeftRearLift, 0, moveDelay);  //lower right front leg
	twitch(LeftRearTibia, 0, moveDelay);  //fix right front Tibia
	twitch(LeftFrontLift, 0, moveDelay);  //lower right rear leg
	twitch(LeftFrontTibia, 0, moveDelay);  //fix right rear Tibia
	twitch(RightMiddleLift, 0, moveDelay);  //lower left middle leg
	twitch(RightMiddleTibia, 0, moveDelay);  //fix left middle Tibia  
	delay(stepDelay);
	twitch(RightRearLift, z_offset, moveDelay);  //raise left front leg 
	twitch(RightFrontLift, z_offset, moveDelay);  //raise left rear leg
	twitch(LeftMiddleLift, z_offset, moveDelay);  //raise Right middle leg
	delay(stepDelay);
	twitch(RightRearRot, -(y_offset), moveDelay);  //move left front leg forward
	twitch(RightFrontRot, -(y_offset), moveDelay);  //move left rear leg forward
	twitch(LeftMiddleRot, -(y_offset), moveDelay);  //move right middle leg forward
	twitch(LeftRearRot, y_offset, moveDelay);  //move right front leg backward
	twitch(LeftFrontRot, y_offset, moveDelay);  //move right rear leg backward
	twitch(RightMiddleRot, y_offset, moveDelay);  //move left middle leg backward
	delay(stepDelay);
	twitch(RightRearLift, 0, moveDelay);  //lower left front leg
	twitch(RightRearTibia, 0, moveDelay);  //fix left front Tibia
	twitch(RightFrontLift, 0, moveDelay);  //lower left rear leg
	twitch(RightFrontTibia, 0, moveDelay);  //fix left rear Tibia
	twitch(LeftMiddleLift, 0, moveDelay);  //lower right middle leg
	twitch(LeftMiddleTibia, 0, moveDelay);  //fix right middle Tibia
	delay(stepDelay);
}

void Walking_Patterns::tripod_left() {
	twitch(RightFrontLift, 30);   //raise left front leg 
	twitch(RightRearLift, 30);   //raise left rear leg
	twitch(LeftMiddleLift, 30);   //raise Right middle leg
	delay(70);
	twitch(RightFrontRot, 15);   //move right front leg backward
	twitch(RightRearRot, 15);   //move right rear leg backward
	twitch(LeftMiddleRot, -15);   //move left middle leg backward
	twitch(LeftFrontRot, 15);   //move left front leg forward
	twitch(LeftRearRot, 15);   //move left rear leg forward
	twitch(RightMiddleRot, -15);   //move right middle leg forward
	delay(70);
	twitch(RightFrontLift, 0);   //raise left front leg 
	twitch(RightRearLift, 0);   //raise left rear leg
	twitch(LeftMiddleLift, 0);   //raise Right middle leg
	twitch(RightFrontTibia, 0);   //raise left front leg 
	twitch(RightRearTibia, 0);   //raise left rear leg
	twitch(LeftMiddleTibia, 0);   //raise Right middle leg
	delay(70);
	twitch(LeftFrontLift, 30);   //raise left front leg 
	twitch(LeftRearLift, 30);   //raise left rear leg
	twitch(RightMiddleLift, 30);   //raise Right middle leg
	delay(70);
	twitch(LeftFrontRot, -15);   //move left front leg forward
	twitch(LeftRearRot, -15);   //move left rear leg forward
	twitch(RightMiddleRot, 15);   //move right middle leg forward
	twitch(RightFrontRot, -15);   //move right front leg backward
	twitch(RightRearRot, -15);   //move right rear leg backward
	twitch(LeftMiddleRot, 15);   //move left middle leg backward
	delay(70);
	twitch(LeftFrontLift, 0);    //lower left front leg
	twitch(LeftRearLift, 0);    //lower left rear leg
	twitch(RightMiddleLift, 0);    //lower right middle leg
	twitch(LeftFrontTibia, 0);    //lower left front leg
	twitch(LeftRearTibia, 0);    //lower left rear leg
	twitch(RightMiddleTibia, 0);    //lower right middle leg
	delay(70);
}

void Walking_Patterns::tripod_right() {
	twitch(LeftFrontLift, 30);   //raise left front leg 
	twitch(LeftRearLift, 30);   //raise left rear leg
	twitch(RightMiddleLift, 30);   //raise Right middle leg
	delay(70);
	twitch(LeftFrontRot, 15);   //move left front leg forward
	twitch(LeftRearRot, 15);   //move left rear leg forward
	twitch(RightMiddleRot, -15);   //move right middle leg forward
	twitch(RightFrontRot, 15);   //move right front leg backward
	twitch(RightRearRot, 15);   //move right rear leg backward
	twitch(LeftMiddleRot, -15);   //move left middle leg backward
	delay(70);
	twitch(LeftFrontLift, 0);    //lower left front leg
	twitch(LeftRearLift, 0);    //lower left rear leg
	twitch(RightMiddleLift, 0);    //lower right middle leg
	twitch(LeftFrontTibia, 0);    //lower left front leg
	twitch(LeftRearTibia, 0);    //lower left rear leg
	twitch(RightMiddleTibia, 0);    //lower right middle leg
	delay(70);
	twitch(RightFrontLift, 30);   //raise left front leg 
	twitch(RightRearLift, 30);   //raise left rear leg
	twitch(LeftMiddleLift, 30);   //raise Right middle leg
	delay(70);
	twitch(RightFrontRot, -15);   //move right front leg backward
	twitch(RightRearRot, -15);   //move right rear leg backward
	twitch(LeftMiddleRot, 15);   //move left middle leg backward
	twitch(LeftFrontRot, -15);   //move left front leg forward
	twitch(LeftRearRot, -15);   //move left rear leg forward
	twitch(RightMiddleRot, 15);   //move right middle leg forward
	delay(70);
	twitch(RightFrontLift, 0);   //raise left front leg 
	twitch(RightRearLift, 0);   //raise left rear leg
	twitch(LeftMiddleLift, 0);   //raise Right middle leg
	twitch(RightFrontTibia, 0);   //raise left front leg 
	twitch(RightRearTibia, 0);   //raise left rear leg
	twitch(LeftMiddleTibia, 0);   //raise Right middle leg
	delay(70);
}

void Walking_Patterns::delay(int seconds)
{
	clock_t endwait;
	endwait = clock() + (seconds / 1000)* CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}

void Walking_Patterns::delayMicroseconds(int seconds)
{
	clock_t endwait;
	endwait = clock() + (seconds / 1000000) * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}

long Walking_Patterns::map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int Walking_Patterns::angle2pwm(int angle) {
	int pulse_len = map(angle, 0, 180, SERVOMIN, SERVOMAX);
	return pulse_len;
}

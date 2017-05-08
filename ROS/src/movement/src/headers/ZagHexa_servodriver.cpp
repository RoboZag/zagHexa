#include <ZagHexa_servodriver.h>
#include <wiringPiI2C.h> 		// for wiringPiWrite/ReadReg8/setup
#include <stdint.h> 			// for uint8_t
#include <iostream> 			// for cout
#include <time.h> 				// for clock_t, CLOCKS_PER_SEC and clock()
#include <math.h> 				// for floor()


ZagHexa_servodriver::ZagHexa_servodriver(uint8_t addr) {
	/* Get the address for communication */
	_i2caddr = addr;
}

void ZagHexa_servodriver::begin(void) {
	/*Set up the communication and return the device ID */
	DeviceID = wiringPiI2CSetup(_i2caddr);
	reset();
}


void ZagHexa_servodriver::reset(void) {
	/* Reset the communication */
	wiringPiI2CWriteReg8(DeviceID, PCA9685_MODE1, 0x00);
}

void ZagHexa_servodriver::setPWMFreq(float freq) {
	/* Modify the communication frequency */
  freq *= 0.9;  // Correct for overshoot in the frequency setting.
  float prescaleval = 25000000.0;
  prescaleval /= 4096.0;
  prescaleval /= freq;
  prescaleval -= 1.0;
  uint8_t prescale = floor(prescaleval + 0.5);
  uint8_t oldmode = wiringPiI2CReadReg8(DeviceID, PCA9685_MODE1);
  uint8_t newmode = (oldmode & 0x7F) | 0x10; // sleep
  wiringPiI2CWriteReg8(DeviceID, PCA9685_MODE1, newmode); // go to sleep
  wiringPiI2CWriteReg8(DeviceID, PCA9685_PRESCALE, prescale); // set the prescaler
  wiringPiI2CWriteReg8(DeviceID, PCA9685_MODE1, oldmode);
  delay(5);
  //  This sets the MODE1 register to turn on auto increment.
  wiringPiI2CWriteReg8(DeviceID, PCA9685_MODE1, oldmode | 0x80);  
}

void ZagHexa_servodriver::setPWM(uint8_t num, uint16_t on, uint16_t off) {
	wiringPiI2CWriteReg8(DeviceID, LED0_ON_L + 4 * num, on & 0xFF);
	wiringPiI2CWriteReg8(DeviceID, LED0_ON_H + 4 * num, on >> 8);
	wiringPiI2CWriteReg8(DeviceID, LED0_OFF_L + 4 * num, off & 0xFF);
	wiringPiI2CWriteReg8(DeviceID, LED0_OFF_H + 4 * num, off >> 8);
}

  /* Additional function for helping to get the minimum value */
int ZagHexa_servodriver::min(int val1, int val2)
{
	if (val1 > val2)
		return val2;
	else if (val2 > val1)
		return val1;
	else
		return 0;
}

  /* Delay function with milliseconds parameter*/
void ZagHexa_servodriver::delay(int mseconds)
{
	/* Save the current time and add the delay then wait*/
	clock_t endwait;
	endwait = clock() + (mseconds / 1000)* CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}

#ifndef _servo_pwm_pi_H
#define _servo_pwm_pi_H

#include <stdint.h>


int file;
char *filename; // = "/dev/i2c-1";
int addr; //  0b01000000;        // The I2C address of the PWM-Hat

class ZagHexaPWM
{
public:
	ZagHexaPWM(uint8_t addr = 0x40);
	void setPWMFreq(int freq);
	void setPWM(int channel, int on, int value);
	void setPin(uint8_t num, uint16_t val, bool invert);
private:
	void initPWMHat();
	void setAllPWM(int on, int off);
};
#endif
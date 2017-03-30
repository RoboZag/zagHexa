#include <servo_pwm_pi.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <math.h>

enum pwm_regs {
  // Registers/etc.
  __MODE1              = 0x00,
  __MODE2              = 0x01,
  __SUBADR1            = 0x02,
  __SUBADR2            = 0x03,
  __SUBADR3            = 0x04,
  __PRESCALE           = 0xFE,
  __LED0_ON_L          = 0x06,
  __LED0_ON_H          = 0x07,
  __LED0_OFF_L         = 0x08,
  __LED0_OFF_H         = 0x09,
  __ALL_LED_ON_L       = 0xFA,
  __ALL_LED_ON_H       = 0xFB,
  __ALL_LED_OFF_L      = 0xFC,
  __ALL_LED_OFF_H      = 0xFD,
  __RESTART            = 0x80,
  __SLEEP              = 0x10,
  __ALLCALL            = 0x01,
  __INVRT              = 0x10,
  __OUTDRV             = 0x04
};

ZagHexaPWM::ZagHexaPWM(uint8_t addr)
{
	addr = addr;
	filename = (char*)"/dev/i2c-1";
}

void ZagHexaPWM::setAllPWM(int on, int off){
	int res;
	res = i2c_smbus_write_byte_data(file, __ALL_LED_ON_L, on & 0xFF);
	if(res < 0)
		perror("resultaterror");

	res = i2c_smbus_write_byte_data(file, __ALL_LED_ON_H, on  >> 8);
	if(res < 0)
		perror("err2");

	res = i2c_smbus_write_byte_data(file, __ALL_LED_OFF_L, off & 0xFF);
	if(res < 0)
		perror("err3");

	res = i2c_smbus_write_byte_data(file, __ALL_LED_OFF_H, off >> 8);
	if(res < 0)
		perror("err4");
};

void ZagHexaPWM::setPWM(int channel,int on, int value){
	int off = value;
	int res;

	res = i2c_smbus_write_byte_data(file, __LED0_ON_L+4*channel, on & 0xFF);
	if(res < 0)
		perror("ierr1");

	res = i2c_smbus_write_byte_data(file, __LED0_ON_H+4*channel, on >> 8);
	if(res < 0)
		perror("ierr2");

	res = i2c_smbus_write_byte_data(file, __LED0_OFF_L+4*channel, off & 0xFF);
	if(res < 0)
		perror("ierr3");

	res = i2c_smbus_write_byte_data(file, __LED0_OFF_H+4*channel, off >> 8);
	if(res < 0)
		perror("ierr4");

	
};

void ZagHexaPWM::setPWMFreq(int freq){
	int prescale;
	char oldmode, newmode;
	int res;

	float prescaleval = 25000000.0; // 25MHz
	prescaleval /= 4096.0;
	prescaleval /= (float)freq;
	prescaleval -= 1.0;

	prescale = floor(prescaleval + 0.5);
	
	nanosleep((const struct timespec[]){{1, 000000L}}, NULL); 

	oldmode = i2c_smbus_read_byte_data(file, __MODE1);
	newmode = (oldmode & 0x7F) | 0x10; // sleep
	
	res = i2c_smbus_write_byte_data(file, __MODE1, newmode); // go to sleep
	if(res < 0)
		perror("serr0");

	res = i2c_smbus_write_byte_data(file, __PRESCALE, (int)(floor(prescale)));
	if(res < 0)
		perror("serr1");

	res = i2c_smbus_write_byte_data(file, __MODE1, oldmode);
	if(res < 0)
		perror("serr2");

	nanosleep((const struct timespec[]){{0, 5000000L}}, NULL);   //sleep 5microsec,

	res = i2c_smbus_write_byte_data(file, __MODE1, oldmode | 0x80);
	if(res < 0)
		perror("serr3");
	


};

void ZagHexaPWM::initPWMHat() {
	int res;
	char mode1res;

	if ((file = open(filename, O_RDWR)) < 0) {
		/* ERROR HANDLING: you can check errno to see what went wrong */
		perror("Failed to open the i2c bus");
		exit(1);
	}

	if (ioctl(file, I2C_SLAVE, addr) < 0) {
		printf("Failed to acquire bus access and/or talk to slave.\n");
		/* ERROR HANDLING; you can check errno to see what went wrong */
		exit(1);
	}

	setAllPWM(0, 0);

	res = i2c_smbus_write_byte_data(file, __MODE2, __OUTDRV);
	if (res < 0)
		perror("erro1");

	res = i2c_smbus_write_byte_data(file, __MODE1, __ALLCALL);
	if (res < 0)
		perror("erro2");

	nanosleep((const struct timespec[]) { {0, 5000000L} }, NULL);   //sleep 5microsec, wait for osci

	mode1res = i2c_smbus_read_byte_data(file, __MODE1);
	mode1res = mode1res & ~__SLEEP; //                 # wake up (reset sleep)

	res = i2c_smbus_write_byte_data(file, __MODE1, mode1res);
	if (res < 0)
		perror("erro3");

	nanosleep((const struct timespec[]) { {0, 5000000L} }, NULL);   //sleep 5microsec, wait for osci
}

void ZagHexaPWM::setPin(uint8_t num, uint16_t val, bool invert)
{
	// Clamp value between 0 and 4095 inclusive.
	val = min(val, 4095);
	if (invert) {
		if (val == 0) {
			// Special value for signal fully on.
			setPWM(num, 4096, 0);
		}
		else if (val == 4095) {
			// Special value for signal fully off.
			setPWM(num, 0, 4096);
		}
		else {
			setPWM(num, 0, 4095 - val);
		}
	}
	else {
		if (val == 4095) {
			// Special value for signal fully on.
			setPWM(num, 4096, 0);
		}
		else if (val == 0) {
			// Special value for signal fully off.
			setPWM(num, 0, 4096);
		}
		else {
			setPWM(num, 0, val);
		}
	}
}

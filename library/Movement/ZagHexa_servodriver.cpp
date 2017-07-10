/*************************************************** 
  This is a library for our Adafruit 16-channel PWM & Servo driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <ZagHexa_servodriver.h>
#include <wiringPiI2C.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

// Set to true to print some debug messages, or false to disable them.
#define ENABLE_DEBUG_OUTPUT false

ZagHexa_servodriver::ZagHexa_servodriver(uint8_t addr) {
	_i2caddr = addr;
}

void ZagHexa_servodriver::begin(void) {
	fd = wiringPiI2CSetup(_i2caddr);
	reset();
}


void ZagHexa_servodriver::reset(void) {
	wiringPiI2CWriteReg8(fd, PCA9685_MODE1, 0x00);
}

void ZagHexa_servodriver::setPWMFreq(float freq) {
  //Serial.print("Attempting to set freq ");
  //Serial.println(freq);
  freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
  float prescaleval = 25000000.0;
  prescaleval /= 4096.0;
  prescaleval /= freq;
  prescaleval -= 1.0;
  if (ENABLE_DEBUG_OUTPUT) {
    //Serial.print("Estimated pre-scale: "); Serial.println(prescaleval);
  }
  uint8_t prescale = floor(prescaleval + 0.5);
  if (ENABLE_DEBUG_OUTPUT) {
    //Serial.print("Final pre-scale: "); Serial.println(prescale);
  }
  
  uint8_t oldmode = wiringPiI2CReadReg8(fd, PCA9685_MODE1);
  uint8_t newmode = (oldmode&0x7F) | 0x10; // sleep
  wiringPiI2CWriteReg8(fd, PCA9685_MODE1, newmode); // go to sleep
  wiringPiI2CWriteReg8(fd, PCA9685_PRESCALE, prescale); // set the prescaler
  wiringPiI2CWriteReg8(fd, PCA9685_MODE1, oldmode);
  delay(5);
  wiringPiI2CWriteReg8(fd, PCA9685_MODE1, oldmode | 0x80);  //  This sets the MODE1 register to turn on auto increment.
                                          // This is why the beginTransmission below was not working.
  //  Serial.print("Mode now 0x"); Serial.println(read8(PCA9685_MODE1), HEX);
}

void ZagHexa_servodriver::setPWM(uint8_t num, uint16_t on, uint16_t off) {
  //Serial.print("Setting PWM "); Serial.print(num); Serial.print(": "); Serial.print(on); Serial.print("->"); Serial.println(off);
	wiringPiI2CWriteReg8(fd, LED0_ON_L + 4 * num, on & 0xFF);
	wiringPiI2CWriteReg8(fd, LED0_ON_H + 4 * num, on >> 8);
	wiringPiI2CWriteReg8(fd, LED0_OFF_L + 4 * num, off & 0xFF);
	wiringPiI2CWriteReg8(fd, LED0_OFF_H + 4 * num, off >> 8);
}

// Sets pin without having to deal with on/off tick placement and properly handles
// a zero value as completely off.  Optional invert parameter supports inverting
// the pulse for sinking to ground.  Val should be a value from 0 to 4095 inclusive.
void ZagHexa_servodriver::setPin(uint8_t num, uint16_t val, bool invert)
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
      setPWM(num, 0, 4095-val);
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

int ZagHexa_servodriver::min(int val1, int val2)
{
	if (val1 > val2)
		return val2;
	else if (val2 > val1)
		return val1;
	else
		return 0;
}
void ZagHexa_servodriver::delay(int seconds)
{
	clock_t endwait;
	endwait = clock() + (seconds / 1000)* CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}

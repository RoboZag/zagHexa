/*************************************************** 
  This is a library for 16-channel PWM Servo driver PCA9685

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Raspberry Pi 3 Modle B, thats SCL ->Pin 5, SDA -> Pin 3

  Written by Mahmoud M. Awadallh for CES Graguation Project "ZagHexa".  
  all text above must be included in any redistribution
 ****************************************************/

#ifndef _ZagHexa_servodriver_H
#define _ZagHexa_servodriver_H
#include "stdint.h"


// define the Controller Registers addresses
#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9



class ZagHexa_servodriver {
 public:
  ZagHexa_servodriver(uint8_t addr = 0x40);
  void begin(void);
  void reset(void);
  void setPWMFreq(float freq);
  void setPWM(uint8_t num, uint16_t on, uint16_t off);
  //void setPin(uint8_t num, uint16_t val, bool invert=false);

 private:
  uint8_t _i2caddr;
  int DeviceID;
  int min(int val1, int val2);
  void delay(int mseconds);
};
#endif

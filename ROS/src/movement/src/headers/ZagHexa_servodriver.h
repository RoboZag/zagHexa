/*****************************************************************************
 Walking Patterns - ZagHexa
 ----------------------------
  
  This is a library for 16-channel PWM Servo driver PCA9685
  

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Raspberry Pi 3 Modle B, thats SCL ->Pin 5, SDA -> Pin 3
  
  Project: CES Graguation Project ZagHexa https://robozag.github.io/zagHexa/
  Author: 
  	Mahmoud M. Awadallh  	mahmoud.elsyed21@gmail.com
  Version: 1.0
  Date: 2017
------------------------------------------------------------------------------
Copyright (c) 2017 ZagHexa, Dr.Ing. Mohammed Nour Abdelgwad Ahmed
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*****************************************************************************/

#ifndef _ZagHexa_servodriver_H
#define _ZagHexa_servodriver_H
#include "stdint.h"


// define the Controller Registers addresses
#define PCA9685_MODE1 	 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L	0x6
#define LED0_ON_H 	0x7
#define LED0_OFF_L 	0x8
#define LED0_OFF_H 	0x9



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

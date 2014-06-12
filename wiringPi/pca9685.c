#include <math.h>

#include "wiringPi.h"
#include "wiringPiI2C.h"

#include "pca9685.h"
#include "pca9685reg.h"

/*
 * myPwmWrite
 *********************************************************************************
 */

static void myPwmWrite (struct wiringPiNodeStruct *node, int pin, int value)
{
    int fd = node->fd;
    int chan = 4 * (pin - node->pinBase);
    
    wiringPiI2CWriteReg8(fd, LED0_ON_L + chan, 0x00);
    wiringPiI2CWriteReg8(fd, LED0_ON_H + chan, 0x00);
    wiringPiI2CWriteReg8(fd, LED0_OFF_L + chan, value & 0xFF);
    wiringPiI2CWriteReg8(fd, LED0_OFF_H + chan, (value >> 8) & 0xFF);
}

/*
 * pca9685Setup:
 *      Create a new wiringPi device node for an pca9685 on the Pi's
 *      I2C interface.
 *********************************************************************************
 */

int pca9685Setup (const int pinBase, const int i2cAddress, const int freq)
{
    int fd;
    struct wiringPiNodeStruct *node;
    
    if ((fd = wiringPiI2CSetup(i2cAddress)) < 0)
        return fd;
        
    wiringPiI2CWriteReg8(fd, MODE1, 0x00); // Reset
    
    int prescale = (int)round(OSC_CLOCK / (PRESCALE_DIVIDER * freq)) - 1; // Calculate presacle
    int mode1 = wiringPiI2CReadReg8(fd, MODE1); // Read MODE1 register
    wiringPiI2CWriteReg8(fd, MODE1, (mode1 & 0x7F) | MODE1_SLEEP); // Write MODE1 register (discard RESTART bit and set SLEEP bit)
    wiringPiI2CWriteReg8(fd, PRE_SCALE, prescale); // Write PRE_SCALE register
    wiringPiI2CWriteReg8(fd, MODE1, mode1); // Restore MODE1 register
    delay(5);
    wiringPiI2CWriteReg8(fd, MODE1, mode1 | MODE1_RESTART); // Write MODE1 register (set RESTART BIT)
    
    node = wiringPiNewNode (pinBase, 16);
    
    node->fd = fd;
    node->pwmWrite = myPwmWrite;
    
    return 0;
}

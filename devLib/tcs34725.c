#include <math.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "tcs34725.h"

static int tcs34725_fds[TCS34725_MAX_TCS34725] = {0};
static int tcs34725_count = 0;

void tcs34725ReadRGBC(int id, unsigned short *r, unsigned short *g, unsigned short *b, unsigned short *c)
{
  int fd = tcs34725_fds[id];
  
  *r = wiringPiI2CReadReg16(fd, TCS34725_RDATAL);
  *g = wiringPiI2CReadReg16(fd, TCS34725_GDATAL);
  *b = wiringPiI2CReadReg16(fd, TCS34725_BDATAL);
  *c = wiringPiI2CReadReg16(fd, TCS34725_CDATAL);
}

// Formulas are from : TAOS Designer's notebook : Calculating Color Temperature and Illuminance using the TAOS TCS3414CS Digital Color Sensor
unsigned short tcs34725GetCorrelatedColorTemperature(unsigned short r, unsigned short g, unsigned short b)
{
  float x = (-0.14282f * r) + (1.54924f * g) + (-0.95641f * b);
  float y = (-0.32466f * r) + (1.57837f * g) + (-0.73191f * b);
  float z = (-0.68202f * r) + (0.77073f * g) + (0.56332f * b);
  
  float xc = x / (x + y + z);
  float yc = y / (x + y + z);
  
  float n = (xc - 0.3320f) / (0.1858f - yc);
  
  float cct = (449.0f * powf(n, 3)) + (3525.0f * powf(n, 2)) + (6823.3f * n) + 5520.33f;
  
  return (unsigned short)cct;
}

unsigned short tcs34725GetIlluminance(unsigned short r, unsigned short g, unsigned short b)
{
  float illuminance = (-0.32466f * r) + (1.57837f * g) + (-0.73191f * b);
  return (unsigned short)illuminance;
}

void tcs34725SetInterrupt(int id, int aien)
{
  int fd = tcs34725_fds[id];
  
  unsigned char enable = wiringPiI2CReadReg8(fd, TCS34725_ENABLE);
  if (aien)
    enable |= TCS34725_ENABLE_AIEN;
  else
    enable &= ~TCS34725_ENABLE_AIEN;
  wiringPiI2CWriteReg8(fd, TCS34725_ENABLE, enable);
}

void tcs34725ClearInterrupt(int id)
{
  int fd = tcs34725_fds[id];
  
  wiringPiI2CWrite(fd, TCS34725_COMMAND_CLEAR_CHANNEL_INTERRUPT | TCS34725_COMMAND_SPECIAL_FUNCTION);
}

void tcs34725SetInterruptLimits(int id, unsigned short low, unsigned short high)
{
  int fd = tcs34725_fds[id];
  
  wiringPiI2CWriteReg8(fd, TCS34725_AILTL, low & 0xFF);
  wiringPiI2CWriteReg8(fd, TCS34725_AILTH, low >> 8);
  wiringPiI2CWriteReg8(fd, TCS34725_AIHTL, high & 0xFF);
  wiringPiI2CWriteReg8(fd, TCS34725_AIHTH, high >> 8);
}

void tcs34725Enable(int id)
{
  int fd = tcs34725_fds[id];
  
  wiringPiI2CWriteReg8(fd, TCS34725_ENABLE_PON);
  delay(3);
  wiringPiI2CWriteReg8(fd, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
}

void tcs34725Disable(int id)
{
  int fd = tcs34725_fds[id];
  
  int enable = wiringPiI2CReadReg8(fd, TCS34725_ENABLE);
  wiringPiI2CWriteReg8(fd, TCS34725_ENABLE, enable & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN));
}

int tcs34725Setup(const int i2cAddress, const int integrationTime, const int gain)
{
  int fd;
  
  if (tcs34725_count == TCS34725_MAX_TCS34725)
    return -1;
  
  if ((fd = wiringPiI2CSetup(i2cAddress)) < 0)
    return fd;
  
  tcs34725_fds[tcs34725_count] = fd;
  
  unsigned char id = wiringPiI2CReadReg8(fd, TCS34725_ID);
  if (id != TCS34725_ID_VALUE)
    return -1;
    
  wiringPiI2CWriteReg8(fd, TCS34725_ATIME, integrationTime & 0xFF); // Write Integration time into ATIME register
  wiringPiI2CWriteReg8(fd, TCS34725_CONTROL, gain & 0x03); // Write gain into CONTROL register
  
  return tcs34725_count++;
}
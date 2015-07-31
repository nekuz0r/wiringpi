#include "wiringPi.h"
#include "wiringPiI2C.h"
#include "dac7678.h"

static void myAnalogWrite (struct wiringPiNodeStruct *node, int pin, int value)
{
  pin -= node->pinBase ;

  unsigned short v = (value << 4);
  v = ((v << 8) & 0xFF00) | ((v >> 8) & 0x00FF);

  wiringPiI2CWriteReg16 (node->fd, DAC7678_WRITE_CHANNEL_CMD | pin, v);
}

static void setVrefMode (struct wiringPiNodeStruct *node, unsigned short vrefMode)
{
  switch (vrefMode) {
    case DAC7678_VREF_MODE_STATIC_OFF: // Static Off
    {
      wiringPiI2CWriteReg16 (node->fd, DAC7678_VREF_MODE_STATIC_CMD, DAC7678_VREF_MODE_STATIC_OFF);
      break;
    }
    case DAC7678_VREF_MODE_STATIC_ON: // Static On
    {
      wiringPiI2CWriteReg16 (node->fd, DAC7678_VREF_MODE_STATIC_CMD, DAC7678_VREF_MODE_STATIC_ON);
      break;
    }
    case DAC7678_VREF_MODE_FLEXIBLE_ON: // Flexible On
    {
      wiringPiI2CWriteReg16 (node->fd, DAC7678_VREF_MODE_FLEXIBLE_CMD, DAC7678_VREF_MODE_FLEXIBLE_ON);
      break;
    }
    case DAC7678_VREF_MODE_FLEXIBLE_ALWAYS_ON: // Flexible Always On
    {
      wiringPiI2CWriteReg16 (node->fd, DAC7678_VREF_MODE_FLEXIBLE_CMD, DAC7678_VREF_MODE_FLEXIBLE_ALWAYS_ON);
      break;
    }
    case DAC7678_VREF_MODE_FLEXIBLE_ALWAYS_OFF: // Flexible Always Off
    {
      wiringPiI2CWriteReg16 (node->fd, DAC7678_VREF_MODE_FLEXIBLE_CMD, DAC7678_VREF_MODE_FLEXIBLE_ALWAYS_OFF);
      break;
    }
    default:
    {
      break;
    }
  }
}

int dac7678Setup (const int pinBase, const int i2cAddress, const unsigned short vrefMode)
{
  int fd ;
  struct wiringPiNodeStruct *node ;

  if ((fd = wiringPiI2CSetup (i2cAddress)) < 0)
    return fd ;

  wiringPiI2CWriteReg16 (fd, DAC7678_RESET_CMD, 0x0000) ;

  node = wiringPiNewNode (pinBase, 8) ;

  node->fd              = fd ;
  node->analogWrite     = myAnalogWrite ;

  setVrefMode (node, vrefMode);

  return 0 ;
}

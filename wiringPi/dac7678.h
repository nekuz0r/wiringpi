#ifdef __cplusplus
extern "C" {
#endif

#define DAC7678_RESET_CMD                     0x70

#define DAC7678_WRITE_CHANNEL_CMD             0x30

#define DAC7678_VREF_MODE_STATIC_CMD          0x80
#define DAC7678_VREF_MODE_FLEXIBLE_CMD        0x90
#define DAC7678_VREF_MODE_STATIC_ON           0x10
#define DAC7678_VREF_MODE_STATIC_OFF          0x00
#define DAC7678_VREF_MODE_FLEXIBLE_ON         (0x40 << 8)
#define DAC7678_VREF_MODE_FLEXIBLE_ALWAYS_ON  (0x50 << 8)
#define DAC7678_VREF_MODE_FLEXIBLE_ALWAYS_OFF (0x60 << 8)
#define DAC7678_VREF_MODE_SWITCH              0x00

extern int dac7678Setup (const int pinBase, const int i2cAddress, const unsigned short vrefMode) ;

#ifdef __cplusplus
}
#endif
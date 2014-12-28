#ifdef __cplusplus
extern "C" {
#endif

#define TCS34725_COMMAND_BIT 0x80
#define TCS34725_COMMAND_CLEAR_CHANNEL_INTERRUPT 0x06
#define TCS34725_COMMAND_SPECIAL_FUNCTION 0x60

#define TCS34725_ENABLE   0x00
#define TCS34725_ATIME    0x01
#define TCS34725_WTIME    0x03
#define TCS34725_AILTL    0x04
#define TCS34725_AILTH    0x05
#define TCS34725_AIHTL    0x06
#define TCS34725_AIHTH    0x07
#define TCS34725_PERS     0x0C
#define TCS34725_CONFIG   0x0D
#define TCS34725_CONTROL  0x0F
#define TCS34725_ID       0x12
#define TCS34725_STATUS   0x13
#define TCS34725_CDATAL   0x14
#define TCS34725_CDATAH   0x15
#define TCS34725_RDATAL   0x16
#define TCS34725_RDATAH   0x17
#define TCS34725_GDATAL   0x18
#define TCS34725_GDATAH   0x19
#define TCS34725_BDATAL   0x1A
#define TCS34725_BDATAH   0x1B

#define TCS34725_ENABLE_AIEN  0x10
#define TCS34725_ENABLE_WEN   0x08
#define TCS34725_ENABLE_AEN   0x02
#define TCS34725_ENABLE_PON   0x01

#define TCS34725_ATIME_2_4MS  0xFF
#define TCS34725_ATIME_24MS   0xF6
#define TCS34725_ATIME_50MS   0xEB
#define TCS34725_ATIME_101MS  0xD5
#define TCS34725_ATIME_154MS  0xC0
#define TCS34725_ATIME_700MS  0x00

#define TCS34725_WTIME_2_4MS  0xFF
#define TCS34725_WTIME_204MS  0xAB
#define TCS34725_WTIME_614MS  0x00

#define TCS34725_PERS_0   0x0
#define TCS34725_PERS_1   0x1
#define TCS34725_PERS_2   0x2
#define TCS34725_PERS_3   0x3
#define TCS34725_PERS_5   0x4
#define TCS34725_PERS_10  0x5
#define TCS34725_PERS_15  0x6
#define TCS34725_PERS_20  0x7
#define TCS34725_PERS_25  0x8
#define TCS34725_PERS_30  0x9
#define TCS34725_PERS_35  0xA
#define TCS34725_PERS_40  0xB
#define TCS34725_PERS_45  0xC
#define TCS34725_PERS_50  0xD
#define TCS34725_PERS_55  0xE
#define TCS34725_PERS_60  0xF

#define TCS34725_CONFIG_WLONG  0x02

#define TCS34725_GAIN_1   0x00
#define TCS34725_GAIN_4   0x01
#define TCS34725_GAIN_16  0x02
#define TCS34725_GAIN_60  0x03

#define TCS34725_ID_VALUE  0x44

#define TCS34725_STATUS_AINT    0x10
#define TCS34725_STATUS_AVALID  0x01

#define TCS34725_MAX_TCS34725  0x08

extern void           tcs34725ReadRGBC                      (int id, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *c);
extern void           tcs34725ReadHSV                       (int id, unsigned short *h, unsigned char *s, unsigned char *v);
extern unsigned short tcs34725GetCorrelatedColorTemperature (unsigned char r, unsigned char g, unsigned char b);
extern unsigned short tcs34725GetIlluminance                (unsigned char r, unsigned char g, unsigned char b);

extern void           tcs34725SetInterrupt                  (int id, int aien);
extern void           tcs34725ClearInterrupt                (int id);
extern void           tcs34725SetInterruptLimits            (int id, unsigned short low, unsigned short high);

extern void           tcs34725Enable                        (int id);
extern void           tcs34725Disable                       (int id);

extern int            tcs34725Setup                         (const int i2cAddress, const int integrationTime, const int gain);

#ifdef __cplusplus
}
#endif
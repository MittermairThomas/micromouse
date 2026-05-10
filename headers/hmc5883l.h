#ifndef HMC5883L_H
#define HMC5883L_H

#include <stdint.h>

#define HMC_ADDRESS (0x1E <<1)

//Adressen
#define HMC_CONFIG_A 0x00
#define HMC_DATA     0x03

extern int16_t hmcOffset;

extern void initHmc(void);

extern int16_t hmcRead(void);

#endif

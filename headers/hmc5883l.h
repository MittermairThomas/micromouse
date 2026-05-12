#ifndef HMC5883L_H
#define HMC5883L_H

#include <stdint.h>

#define HMC_ADDRESS (0x1E <<1)

//Adressen
#define HMC_CONFIG_A 0x00
#define HMC_DATA     0x03

struct HmcData {
    int16_t x;
    int16_t y;
    int16_t z;

    int16_t xOffset;
    int16_t yOffset;
    int16_t zOffset;
};

extern struct HmcData hmc;

extern void initHmc(void);

extern void hmcRead(struct HmcData* _hmc);

#endif

#ifndef VL53LX_H
#define VL53LX_H

#include <stdint.h>

#define VL53_ADDRESS (0x29 <<1)

#define VL53_INT_PIN PD2

struct Vl53 {
    int8_t offSet;

    uint8_t xShutPin;

    volatile uint8_t* xShutPort;
};

extern void initVl53(void);

extern uint16_t vl53GetDist(struct Vl53* _sensor);

#endif

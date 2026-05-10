#ifndef STEPPER_H
#define STEPPER_H

//---INCLUDES---
#include <stdint.h>

//---DEFINES---
#define STAND      0
#define FORWARD    1
#define BACKWARD   2
#define ROTATE_CW  3
#define ROTATE_CCW 4

struct Stepper {
    uint8_t stepCounter;

    volatile uint8_t* port;

    union {
        uint8_t pins[4];
        
        struct {
            uint8_t aIn1;
            uint8_t aIn2;
            uint8_t bIn1;
            uint8_t bIn2;
        };
    };
};

extern void initStepper(void);

extern void stepperSetDir(uint8_t _dir);

#endif

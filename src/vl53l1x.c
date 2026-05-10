//Code ab Zeile 115

#include "../config.h"

struct Vl53 left;
struct Vl53 front;
struct Vl53 right;

const uint8_t sensorConfig[91] = {
0x00, //0x2D: I2C slow
0x01, //0x2E: Intern I2C pull-up to 2.8V
0x01, //0x2F: GPIO pull-up to 2.8V
0x11, //0x30: GIOP active low
0x02, //0x31: Interrupt puts GPIO to active

0x00, //0x32: not user-modifiable
0x02, //0x33: not user-modifiable
0x08, //0x34: not user-modifiable
0x00, //0x35: not user-modifiable
0x08, //0x36: not user-modifiable
0x10, //0x37: not user-modifiable
0x01, //0x38: not user-modifiable
0x01, //0x39: not user-modifiable
0x00, //0x3a: not user-modifiable
0x00, //0x3b: not user-modifiable
0x00, //0x3c: not user-modifiable
0x00, //0x3d: not user-modifiable
0xff, //0x3e: not user-modifiable
0x00, //0x3f: not user-modifiable
0x0F, //0x40: not user-modifiable
0x00, //0x41: not user-modifiable
0x00, //0x42: not user-modifiable
0x00, //0x43: not user-modifiable
0x00, //0x44: not user-modifiable
0x00, //0x45: not user-modifiable

0x20, //0x46: Interrupt when data ready

0x0b, //0x47: not user-modifiable
0x00, //0x48: not user-modifiable
0x00, //0x49: not user-modifiable
0x02, //0x4a: not user-modifiable
0x0a, //0x4b: not user-modifiable
0x21, //0x4c: not user-modifiable
0x00, //0x4d: not user-modifiable
0x00, //0x4e: not user-modifiable
0x05, //0x4f: not user-modifiable
0x00, //0x50: not user-modifiable
0x00, //0x51: not user-modifiable
0x00, //0x52: not user-modifiable
0x00, //0x53: not user-modifiable
0xc8, //0x54: not user-modifiable
0x00, //0x55: not user-modifiable
0x00, //0x56: not user-modifiable
0x38, //0x57: not user-modifiable
0xff, //0x58: not user-modifiable
0x01, //0x59: not user-modifiable
0x00, //0x5a: not user-modifiable
0x08, //0x5b: not user-modifiable
0x00, //0x5c: not user-modifiable
0x00, //0x5d: not user-modifiable
0x01, //0x5e: not user-modifiable
0xcc, //0x5f: not user-modifiable
0x0f, //0x60: not user-modifiable
0x01, //0x61: not user-modifiable
0xf1, //0x62: not user-modifiable
0x0d, //0x63: not user-modifiable

0x01, //0x64: Sigma threshold
0x68, //0x65: Sigma threshold
0x00, //0x66: Minimum Signal strength
0x80, //0x67. Minimum Signal strength

0x08, //0x68: not user-modifiable
0xb8, //0x69: not user-modifiable
0x00, //0x6a: not user-modifiable
0x00, //0x6b: not user-modifiable

0x00, //0x6c: Not important for manual mode
0x00, //0x6d: Not important for manual mode
0x0F, //0x6e: Not important for manual mode
0x89, //0x6f: Not important for manual mode

0x00, //0x70: not user-modifiable
0x00, //0x71: not user-modifiable

0x00, //0x72: Upper limit for window
0x00, //0x73: Upper limit for window
0x00, //0x74: Lower limit for window
0x00, //0x75: Lower limit for window

0x00, //0x76: not user-modifiable
0x01, //0x77: not user-modifiable
0x0f, //0x78: not user-modifiable
0x0d, //0x79: not user-modifiable
0x0e, //0x7a: not user-modifiable
0x0e, //0x7b: not user-modifiable
0x00, //0x7c: not user-modifiable
0x00, //0x7d: not user-modifiable
0x02, //0x7e: not user-modifiable

0xc7, //0x7F: Whitch part of sensor to use
0xff, //0x80: Whitch part of sensor to use

0x9B, //0x81: not user-modifiable
0x00, //0x82: not user-modifiable
0x00, //0x83: not user-modifiable
0x00, //0x84: not user-modifiable
0x01,  //0x85: not user-modifiable

0x00, //0x86: Clear Interrupt
0x00  //0x87: No autostart
};

void initVl53(void) {
    DDRD &= ~(1<<VL53_INT_PIN);

    uint8_t add = 0;

    left.xShutPort = &PORTD;
    left.xShutPin = PD2;
    left.offSet = 0; //Getesteter Wert

    front.xShutPort = &PORTB;
    front.xShutPin = PB4;
    front.offSet = 0;

    right.xShutPort = &PORTB;
    right.xShutPin = PB5;
    right.offSet = 0;

    *(left.xShutPort) |= 1<<left.xShutPin;

    for (add = 0x2D; add <= 0x87; add++) {
        twiStart();
        twiWriteByte(VL53_ADDRESS | MASTER_TX);
        twiWriteByte(0x00);
        twiWriteByte(add);
        twiWriteByte(sensorConfig[add -0x2D]);
        twiStop();
    }
    
    *(left.xShutPort) &= ~(1<<left.xShutPin);

    *(front.xShutPort) |= 1<<front.xShutPin;

    for (add = 0x2D; add <= 0x87; add++) {
        twiStart();
        twiWriteByte(VL53_ADDRESS | MASTER_TX);
        twiWriteByte(0x00);
        twiWriteByte(add);
        twiWriteByte(sensorConfig[add -0x2D]);
        twiStop();
    }
    
    *(front.xShutPort) &= ~(1<<front.xShutPin);

    *(right.xShutPort) |= 1<<right.xShutPin;

    for (add = 0x2D; add <= 0x87; add++) {
        twiStart();
        twiWriteByte(VL53_ADDRESS | MASTER_TX);
        twiWriteByte(0x00);
        twiWriteByte(add);
        twiWriteByte(sensorConfig[add -0x2D]);
        twiStop();
    }
    
    *(right.xShutPort) &= ~(1<<right.xShutPin);
}

uint16_t vl53GetDist(struct Vl53* _sensor) {
    uint8_t buf[2];

    *(_sensor->xShutPort) |= 1<<_sensor->xShutPin;

    twiStart();
    twiWriteByte(VL53_ADDRESS | MASTER_TX);
    twiWriteByte(0x00);
    twiWriteByte(0x87);
    twiWriteByte(0x40);
    twiStop();

    while (PIND & 1<<VL53_INT_PIN);

    twiStart();
    twiWriteByte(VL53_ADDRESS | MASTER_TX);
    twiWriteByte(0x00);
    twiWriteByte(0x96);
    twiStart();
    twiWriteByte(VL53_ADDRESS | MASTER_RX);
    buf[0] = twiReadByteAck();
    buf[1] = twiReadByteNack();
    twiStop();

    twiStart();
    twiWriteByte(VL53_ADDRESS | MASTER_TX);
    twiWriteByte(0x00);
    twiWriteByte(0x86);
    twiWriteByte(0x01);
    twiStop();

    twiStart();
    twiWriteByte(VL53_ADDRESS | MASTER_TX);
    twiWriteByte(0x00);
    twiWriteByte(0x87);
    twiWriteByte(0x00);
    twiStop();

    *(_sensor->xShutPort) &= ~(1<<_sensor->xShutPin);

    return ((uint16_t)(buf[0] <<8)) | buf[1];
}

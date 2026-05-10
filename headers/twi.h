#ifndef TWI_H
#define TWI_H

#include <stdint.h>

#define MASTER_TX 0
#define MASTER_RX 1

extern void initTwi(void);

extern void twiStart(void);
extern void twiStop(void);

extern void twiWriteByte(uint8_t _data);

extern uint8_t twiReadByteAck(void);
extern uint8_t twiReadByteNack(void);

extern void writeReg(uint8_t _address, uint8_t _reg, uint8_t _data);

#endif

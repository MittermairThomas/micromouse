#include "../config.h"

void initTwi(void) {
    TWBR = 72; //100kHz
    TWSR = 0;
    TWCR = 1<<TWEN;
}

void twiStart(void) {
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while(!(TWCR & 1<<TWINT));
}

void twiStop(void) {
    TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);

    //while(!(TWCR & 1<<TWSTO));
}

void twiWriteByte(uint8_t _data) {
    TWDR = _data;

    TWCR = (1<<TWINT) | (1<<TWEN);
    while(!(TWCR & 1<<TWINT));
}

uint8_t twiReadByteAck(void) {
    TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
    while(!(TWCR & 1<<TWINT));

    return TWDR;
}

uint8_t twiReadByteNack(void) {
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(!(TWCR & 1<<TWINT));

    return TWDR;
}

void writeReg(uint8_t _address, uint8_t _reg, uint8_t _data) {
    twiStart();
    twiWriteByte(_address | MASTER_TX);
    
    twiWriteByte(_reg);
    twiWriteByte(_data);

    twiStop();
}

#include "../config.h"

int16_t hmcOffset = 0; //Gemessener wert

void initHmc(void) {
    twiStart();

    twiWriteByte(HMC_ADDRESS | MASTER_TX);
    
    twiWriteByte(HMC_CONFIG_A);
    twiWriteByte(0x70);
    twiWriteByte(0xA0);
    twiWriteByte(0x00);

    twiStop();
}

int16_t hmcRead(void) {
    uint8_t i = 0;

    int16_t hmcData = 0;

    twiStart();

    twiWriteByte(HMC_ADDRESS | MASTER_TX);
    twiWriteByte(HMC_DATA);

    twiStart();

    twiWriteByte(HMC_ADDRESS | MASTER_RX);

    hmcData = twiReadByteAck() <<8;
    hmcData |= twiReadByteAck();

    for (i = 0; i <= 3; i++)
        (void) twiReadByteAck();

    (void) twiReadByteNack();

    twiStop();

    return hmcData + hmcOffset;
}

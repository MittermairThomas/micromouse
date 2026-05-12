#include "../config.h"

struct HmcData hmc = {0};

void initHmc(void) {
    twiStart();

    twiWriteByte(HMC_ADDRESS | MASTER_TX);
    
    twiWriteByte(HMC_CONFIG_A);
    twiWriteByte(0x70);
    twiWriteByte(0xA0);
    twiWriteByte(0x00);

    twiStop();
}

void hmcRead(struct HmcData* _pHmc) {
    twiStart();

    twiWriteByte(HMC_ADDRESS | MASTER_TX);
    twiWriteByte(HMC_DATA);

    twiStart();

    twiWriteByte(HMC_ADDRESS | MASTER_RX);

    _pHmc->x = twiReadByteAck() <<8;
    _pHmc->x |= twiReadByteAck();

    _pHmc->x += _pHmc->xOffset;

    _pHmc->z = twiReadByteAck() <<8;
    _pHmc->z |= twiReadByteAck();

    _pHmc->z += _pHmc->zOffset;

    _pHmc->y = twiReadByteAck() <<8;
    _pHmc->y |= twiReadByteAck();

    _pHmc->y += _pHmc->yOffset;

    twiStop();
}

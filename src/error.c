#include "../config.h"

void initError(void) {
    DDRC |= 0x0F;

    PORTC &= ~(0x0F);
}

void clearError(void) {
    PORTC &= ~(0x0F);
}

void error(uint8_t _error) {
    if (_error > 0x0F)
        return;
    clearError();
    PORTC |= _error;
}

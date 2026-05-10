#ifndef ERROR_H
#define ERROR_H

#include <stdint.h>

#define NO_ERROR 0x00
//Keine Meldung

#define INIT 0x01
//UMC initialisiert Sensoren, Schnittstellen ect.

extern void initError(void);

extern void clearError(void);
extern void error(uint8_t _error);

#endif

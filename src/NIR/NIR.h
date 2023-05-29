#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include "TWI/TWI.h"

#ifndef NIR_H
#define NIR_H

// Funksjons dekalrasjoner for kontroll av NIR-lys.
void initTimer2();
void startNIR(uint8_t NIRmode, uint8_t NIRfreq, uint8_t R_ID);
void endNIR(void);

#endif
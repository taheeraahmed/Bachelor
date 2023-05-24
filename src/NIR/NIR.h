#include <avr/interrupt.h>
#include <avr/io.h>
#include "TWI/TWI.h"

#ifndef NIR_H
#define NIR_H

// Funksjons dekalrasjoner for kontroll av NIR-lys.
void initTimer0();
void initNIR(uint8_t NIRDuty, uint8_t R_ID);
void endNIR(void);

#endif
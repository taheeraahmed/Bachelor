#include <avr/interrupt.h>
#include <avr/io.h>

#ifndef NIR_H
#define NIR_H

void initTimer0();
void initNIR(uint8_t NIRDuty, uint8_t R_ID);

extern "C" void TIMER0_COMPA_vect (void);
extern "C" void TIMER0_OVF_vect (void);  

#endif
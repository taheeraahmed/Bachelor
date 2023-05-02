#include <avr/interrupt.h>
#include <avr/io.h>

#ifndef NIR_H
#define NIR_H

uint16_t ledRID[4] = {0, 1000, 10000, 51000};
uint16_t ledWaveLength[4] = {0, 660, 810, 880};
uint8_t numEnPins[4] = {0, 1, 3, 3};
uint8_t nirData[3];
uint8_t arrayLength = 3;

void initTimer0();
void initNIR(uint8_t NIRDuty, uint8_t R_ID);

extern "C" void TIMER0_COMPA_vect (void);
extern "C" void TIMER0_OVF_vect (void);  

#endif
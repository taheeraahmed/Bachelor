#include <avr/interrupt.h>


#ifndef LED_H
#define LED_H

extern volatile bool greenButtonTrigg;

// Her deklareres alle funksjoner som kontrollerer LED-ene på styringsenheten
void initLedPins(void);
void redLedOn(void);
void redLedBlink(void);
void redLedOff(void);
void greenLedOn(void);
void greenLedBlink(void);
void greenLedOff(void);
void testIndicatorOn(void);
void testIndicatorOff(void);
void initPinChangeInterrupt(void);

#endif // !LED_H

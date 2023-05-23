
#ifndef LED_H_
#define LED_H_

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

#endif // !LED_H

#ifndef getTime_H_
#define getTime_H_

#include <avr/interrupt.h>

ISR (TIMER1_COMPA_vect);
void initGetTime(void);
unsigned long getTime(void);

#endif
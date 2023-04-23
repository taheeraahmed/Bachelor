#include <avr/io.h>

void initPWM(void);
void setDutyCycle(uint8_t dutyCycle);
ISR(TIMER0_COMPA_vect);
ISR(TIMER0_OVF_vect);
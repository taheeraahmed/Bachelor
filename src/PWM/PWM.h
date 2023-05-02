#include <avr/io.h>

#ifndef PWM_H
#define PWM_H

void initTimer1();
void setBuzzerAlarm(bool buzzerState, uint8_t buzzDuty);
void setFans(bool controllFans, bool ledFans, uint8_t controllFanDuty, uint8_t ledFanDuty);

extern "C" void TIMER1_COMPA_vect (void);
extern "C" void TIMER1_COMPB_vect (void);
extern "C" void TIMER1_COMPC_vect (void);
extern "C" void TIMER1_OVF_vect (void);  

#endif
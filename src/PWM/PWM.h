
#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <getTime/getTime.h>

void initTimer3(void);
void setBuzzerAlarm(bool buzzerState, uint8_t buzzDuty, uint16_t interval);
void setFans(bool controllFans, bool ledFans, uint8_t controllFanDuty, uint8_t ledFanDuty);

extern "C" void TIMER3_COMPA_vect (void);
extern "C" void TIMER3_COMPB_vect (void);
extern "C" void TIMER3_COMPC_vect (void);
extern "C" void TIMER3_OVF_vect (void);  

#endif
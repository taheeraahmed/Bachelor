#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <getTime/getTime.h>

void initTimer3(void);
void setBuzzerAlarm(bool buzzerState, uint8_t buzzDuty, uint16_t interval);
void setFans(bool controllFans, bool ledFans, uint8_t controllFanDuty, uint8_t ledFanDuty);

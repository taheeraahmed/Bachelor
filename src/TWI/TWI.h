#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <string.h>

#ifndef TWI_H_
#define TWI_H_

//Funksjonsdefinisjoner:
void initTWI(void);
void TWIStartTx(uint8_t address, uint8_t write_reg, uint8_t write_data);
void TWIStartRx(uint8_t address, uint8_t read_register);
void TWIStartCond(void);
void TWIWrite(uint8_t data);
uint8_t TWIRecieveWithAck(void);
uint8_t TWIRecieveWithNack(void);
void TWIStopCond(void);

void getDate(void);
char *formatDateToChar(uint8_t dateArray[3]);
void getTimeStamp(void);
char *formatTimeToChar(uint8_t timeArray[3]);
char *formatDateTimeToChar(uint8_t dateArray[3], uint8_t timeArray[3]);
void resetRTC(uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year);

void getBatteryState(void);
void setDAC(bool on_off);

// Globale varialbler som innholder returrn veridiene for getDate og getTimeStamp.
extern uint8_t calcDate[3];
extern uint8_t calcTime[3];
extern uint8_t batteryState[3];

extern char timeChar[8];
extern char dateChar[8];
extern char dateTimeChar[17];


#endif // !TWI_H

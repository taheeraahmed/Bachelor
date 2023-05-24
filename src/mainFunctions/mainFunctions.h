#include <avr/io.h>

#include "ledControls/ledControls.h"
#include "NIR/NIR.h"
#include "getTime/getTime.h"
#include "PWM/PWM.h"
#include "Temp/Temp.h"
#include "TWI/TWI.h"
#include "writeToFile/writeToFile.h"
#include "menu/menu.h"

#ifndef mainFunctions_H
#define mainFunctions_H

extern volatile bool greenButtonTrigg;

void initiateSystem(void);
void testDataUpdate(unsigned long testLength);
void setSystemSleep(void);
char *getRemainingSeconds(unsigned long start, unsigned long duration);
char *getRemainingMinutes(unsigned long start, unsigned long duration);
void initPinChangeInterrupt(void);
void runSystem(void);

#endif // !
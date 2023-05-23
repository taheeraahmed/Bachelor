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

void initiateSystem(void);
void runMenu(void);
void testDataUpdate(unsigned long testLength);
void setSystemSleep(void);
uint8_t getRemainingSeconds(unsigned long start, unsigned long duration);
uint8_t getRemainingMinutes(unsigned long start, unsigned long duration);
#endif // !
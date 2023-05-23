#include <avr/io.h>

#include "ledControls/ledControls.h"
#include "NIR/NIR.h"
#include "getTime/getTime.h"
#include "PWM/PWM.h"
#include "Temp/Temp.h"
#include "TWI/TWI.h"
#include "writeToFile/writeToFile.h"

#ifndef mainFunctions_H
#define mainFunctions_H

void initiateSystem(void);
void runMenu(void);
void runTest(unsigned long testLength);
void systemExit(void);
#endif // !
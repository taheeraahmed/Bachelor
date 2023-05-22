#ifndef MENU_H
#define MENU_H

#include <avr/io.h>
#include <stdbool.h>
#include <Arduino.h>
#include <util/delay.h>
#include "Screen/Screen.h"
#include "Keypad.h"

void RunMenu(void);
void waitForPassword(void);
void setPatientID(void);
void setTime();
void showLed(uint8_t ledHead);
void chooseNIRsettings(void);
void chooseMode(void);
void showSettings(void);
void SaveOrExit(void);
void systemWaiting(void);

#endif
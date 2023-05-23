#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "logoGray.h"

#ifndef SCREEN_H
#define SCREEN_H

void initScreen();
void clearScreen();
void homeScreen();


void drawtextHeading(char *text, uint16_t color);
void drawtextSkinContact(char *text, uint16_t color);
void drawtextDate(char *text, uint16_t color);
void drawtextNormal(char *text, uint16_t color);

//Skjermbildene for å kjøre koden til "RunSientistMenu"
void setPasswordScreen();
void setPatientIDScreen();
void chooseTimeScreen();
void getLEDHeadScreen();
void pulseNIRSettingsScreen();
void chooseModeScreen();
void showSettingsScreen();
void SaveOrExitScreen();

//Skjermbildene for å kjøre koden til "RunUserMenu"
void getSkinContactScreen();
void selectStartButtonScreen();
void runExperimentScreen();
void exitExperimentScreen();

//Skjermbildene for feilmeldinger på skjermen
void wrongPasswordScreen();
void overheatingScreen();
void noSkinContactScreen();

//Firkanter med tekst og fargefyll for å indikere status på hudkontakten
void greenRectangle();
void yellowRectangle();
void redRectangle();

unsigned char batteryState(uint8_t batterycharge);

#endif
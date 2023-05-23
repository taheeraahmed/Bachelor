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
void homeScreen(uint8_t battery, char date[8]);
void batteryCharge(uint8_t battery_charge);
void skinContactStatus(uint8_t skin_contact);

//unsigned char batteryUpdate(uint8_t battery_charge); //fjerne kanskje?


void drawtextHeading(char *text, uint16_t color);
void drawtextSkinContact(char *text, uint16_t color);
void drawtextDate(char *text, uint16_t color);
void drawtextNormal(char *text, uint16_t color);

//Skjermbildene for å kjøre koden til "RunSientistMenu"
void setPasswordScreen(uint8_t battery, char date[8]);
void setPatientIDScreen(uint8_t battery, char date[8]);
void chooseTimeScreen(uint8_t battery, char date[8]);
void getLEDHeadScreen(uint8_t battery, char date[8]);
void pulseNIRSettingsScreen(uint8_t battery, char date[8]);
void chooseModeScreen(uint8_t battery, char date[8]);
void showSettingsScreen(uint8_t battery, char date[8]);
void SaveOrExitScreen(uint8_t battery, char date[8]);

//Skjermbildene for å kjøre koden til "RunUserMenu"
void getSkinContactScreen(uint8_t battery, char date[8], uint8_t skin_contact);
void selectStartButtonScreen(uint8_t battery, char date[8], uint8_t skin_contact);
void runExperimentScreen(uint8_t battery, char date[8], char remaining_seconds[2], char remaining_minutes[2], uint8_t skin_contact);
void exitExperimentScreen(uint8_t battery, char date[8]);

//Skjermbildene for feilmeldinger på skjermen
void wrongPasswordScreen(uint8_t battery, char date[8]);
void overheatingScreen();
void noSkinContactScreen();

//Firkanter med tekst og fargefyll for å indikere status på hudkontakten
void greenRectangle();
void yellowRectangle();
void redRectangle();

unsigned char batteryState(uint8_t batterycharge);

#endif
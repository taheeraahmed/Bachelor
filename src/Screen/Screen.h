#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "logoGray.h"
#include "utils/utils.h"

#ifndef SCREEN_H
#define SCREEN_H

void initScreen();
void clearScreen();
void homeScreen(uint8_t battery, char date[8]);

// Oppdatering av batteriprosent og 
void batteryCharge(uint8_t battery_charge);
void skinContactStatus(uint8_t skin_contact);
void drawDateAndBatteyCharge(uint8_t battery_charge, char date[8]);

//Skjermbildene for å kjøre koden til "RunScientistMenu"
void setPasswordScreen(uint8_t battery, char date[8]);
void setPatientIDScreen(uint8_t battery, char date[8]);
void chooseTimeScreen(uint8_t battery, char date[8]);
void getLEDHeadScreen(uint8_t battery, char date[8]);
void pulseNIRSettingsScreen(uint8_t battery, char date[8]);
void chooseModeScreen(uint8_t battery, char date[8]);
void showSettingsScreen(uint8_t battery, char date[8], TestChoices test_choices);
void SaveOrExitScreen(uint8_t battery, char date[8]);

//Skjermbildene for å kjøre koden til "RunUserMenu"
void getSkinContactScreen(uint8_t battery, char date[8], uint8_t skin_contact);
void selectStartButtonScreen(uint8_t battery, char date[8], uint8_t skin_contact);
void runExperimentScreen(uint8_t battery, char date[8], char remaining_seconds[2], char remaining_minutes[2], uint8_t skin_contact);
void exitExperimentScreen(uint8_t battery, char date[8]);

//Skjermbildene for feilmeldinger på skjermen
void wrongPasswordScreen(uint8_t battery, char date[8]);
void criticalErrorScreen();
void noSkinContactScreen();

//Firkanter med plassering tekst og fargefyll for å indikere status på hudkontakten
void greenRectangle();
void yellowRectangle();
void redRectangle();

#endif
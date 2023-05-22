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

void drawtextHeading(char *text, uint16_t color);
void drawtextSkinContact(char *text, uint16_t color);
void drawtextDate(char *text, uint16_t color);
void drawtextNormal(char *text, uint16_t color);


void homeScreen();
void setPasswordScreen();
void setPatientIDScreen();
void chooseTimeScreen();
void getLEDHeadScreen();
void NIRSettingsScreen();
void chooseModeScreen();
void showSettingsScreen();
void SaveOrExitScreen();
void wrongPasswordScreen();

//Firkanter med tekst og fargefyll for å indikere status på hudkontakten
void greenRectangle();
void yellowRectangle();
void redRectangle();

unsigned char batteryState(uint8_t batterycharge);

#endif
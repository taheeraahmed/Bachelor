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
void headingdrawtext(char *text, uint16_t color);
void skinContactdrawtext(char *text, uint16_t color);
void testdrawtext(char *text, uint16_t color);
unsigned char batteryState(uint8_t batterycharge);
void homeScreen();
void clearScreen();

//Firkanter med tekst og fargefyll for å indikere status på hudkontakten
void greenRectangle();
void yellowRectangle();
void redRectangle();

#endif
#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

#ifndef KEYPAD_H
#define KEYPAD_H

void initKeypad();
void getKey();

#endif
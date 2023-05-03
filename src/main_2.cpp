#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include "Keypad/Keypad.h"


void setup() {
Serial.begin(9600);
initKeypad();

}

void loop() {
getKey();
}
#include <Arduino.h>
#include "utils.h"

void turnOnFans(FAN_PINS fan_pins) {
    analogWrite(fan_pins.CONTROL, 255);
    analogWrite(fan_pins.LED, 255);
}

void turnOffFans(FAN_PINS fan_pins) {
    analogWrite(fan_pins.CONTROL, 0);
    analogWrite(fan_pins.LED, 0);
}

/*
void initFans(){
    // Setter pinnene til viftene som Output.
    DDRB |= (1 << PIN5) | (1 << PIN4);
};

void turnOnFans() {
    PORTB |= (1 << PIN5) | (1 << PIN4);
}

void turnOffFans() {
    PORTB &= ~((1 << PIN5) | (1 << PIN4));
}
*/
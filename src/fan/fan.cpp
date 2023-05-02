#include <Arduino.h>

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
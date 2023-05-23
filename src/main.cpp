#include "mainFunctions/mainFunctions.h"
#include <Adafruit_I2CDevice.h>

void initPinChangeInterrupt(void);
uint8_t system_state = 0;

int main(void){

  initPinChangeInterrupt();
  initiateSystem();
  return 0;
}


void initPinChangeInterrupt(void){
  // Setting  
  DDRJ &= ~(1 << PIN1);
  
  // set up interrupt vector table
  PCICR |= (1 << PIN1); // Enable PCINT for Port J
  PCMSK1 |= (1 << PIN1); // Enable PCINT3 for PORTJ PIN!
}

ISR(PCINT1_vect){
  SMCR &= ~((1 << PIN2) | (1 << PIN0));
}
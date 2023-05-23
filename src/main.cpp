#include <mainFunctions/mainFunctions.h>
#include <Adafruit_I2CDevice.h>


void initPinChangeInterrupt(void);
uint8_t system_state = 0;

void setup(void){

  initPinChangeInterrupt();
  initiateSystem();
}

void loop(void){
  testDataUpdate(3000);
}

void systemFlow(void){
  switch (system_state){
    case 0:
      // Sleeping
      setSystemSleep();
      break;
    case 1:
      // System is initiated
      initiateSystem();
      // APT logo is shown
      // systemWaiting();
      break;
  }
}


void initPinChangeInterrupt(void){
  // Setting  
  DDRJ &= ~(1 << PIN1);
  
  // set up interrupt vector table
  PCICR |= (1 << PIN1); // Enable PCINT for Port J
  PCMSK1 |= (1 << PIN1); // Enable PCINT3 for PORTJ PIN!
}

ISR(PCINT1_vect){
  if (system_state == 0){
    SMCR &= ~((1 << PIN2) | (1 << PIN0));
    system_state = 1;
  }
}
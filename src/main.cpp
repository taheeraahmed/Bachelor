#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <Temp/Temp.h>
#include "getTime/getTime.h"
#include "utils.h"
#include <stdio.h>

/*
Trigger en interrupt hver gang timer er lik ett millisekund.
Arduino MEGA 2560 har 16MHz

16MHz/1000 som deles på en prescale 8 gir oss 2000. Hver gang 
teller er 2000 så har ett millisekund gått. Dette kan vi lage til en macro
*/


int main(void)
{
  Serial.begin(9600);
  initADC();
  initPort();
  calcLedID();
  initGetTime();

  DDRB |= (1<< PIN7);
  PORTB |= (1<< PIN7);

  while (1)
  {
   printADC();
   _delay_ms(2000);

    unsigned long getTime_current = getTime();
    long getTime_since;

      if(getTime_current - getTime_since > 2000) {
        // LED connected to PC0/Analog 0
        PORTB ^= (1 << PIN7);
        getTime_since = getTime_current;
    }
  }
  
}

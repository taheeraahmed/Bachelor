#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <Temp/Temp.h>
#include "getTime/getTime.h"

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

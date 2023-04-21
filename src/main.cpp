#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <Temp/Temp.h>

int main(void)
{
  Serial.begin(9600);
  initADC();
  initPort();
  calcLedID();

  while (1)
  {
   printADC();
   _delay_ms(2000);
  }
  
}

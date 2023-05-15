#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <Temp/Temp.h>
#include "getTime/getTime.h"

int main(void)
{
 // Serial.begin(9600);

  initADC();
  initPort();
  initGetTime();

  //Serial.print("LED_ID:    ");
  //Serial.println(ID_NIR_LED);

  while (1)
  {
    printADC();
      
  }
  
}
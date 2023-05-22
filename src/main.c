#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <Temp/Temp.h>
#include "getTime/getTime.h"
#include "getError/getError.h"

int main(void)
{
  initADC();
  initPort();
  initGetTime();

  while (1)
  {
    setFlaggADC();
    getError();
  }
}
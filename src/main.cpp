#include <Arduino.h>
#include <stdio.h>
//#include <utils.h>
#include <fan.h>
#include <I2C/I2C.h>
#include <BlinkeLed.h>
#include "PWM/PWM.h"


int main() {
  initTimer1();

  while (1){
    //Test av PWM på led
    setBuzzerAlarm(1,200);
    setFans(1,0,255,0);
  }
  return 0; 
}



#include <Arduino.h>
#include <stdio.h>
//#include <utils.h>
#include <fan.h>
#include <I2C/I2C.h>
#include <BlinkeLed.h>
#include "PWM/PWM.h"

MEMORY_EXTENSION_PINS mem_ext_pins;
TEMPERATURE_PINS temp_pins;
FAN_PINS fan_pins;
TestChoices choices;

int main() {
  pinMode(fan_pins.CONTROL, OUTPUT);
  pinMode(fan_pins.LED, OUTPUT);

  initI2C(100000);
  initPWM();

  //mainI2C();
  while (1){
    //Test av PWM på led
    setDutyCycle(137);  
  }
  return 25; //Cursed
}



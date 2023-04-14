#include <Arduino.h>
#include <stdio.h>
#include <utils.h>
#include <fan.h>
#include <I2C/I2C.h>

MEMORY_EXTENSION_PINS mem_ext_pins;
TEMPERATURE_PINS temp_pins;
FAN_PINS fan_pins;
TestChoices choices;

void main() {
  pinMode(fan_pins.CONTROL, OUTPUT);
  pinMode(fan_pins.LED, OUTPUT);

  init_I2C(100000);

  mainI2C();
  
  while (1){
    
  }
}



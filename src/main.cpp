#include <Arduino.h>
#include <utils.h>
#include <fan.h>

// TODO: Se hvordan kretsskjemaet til PCB er laget og sammenligne med dette

MEMORY_EXTENSION_PINS mem_ext_pins;
TEMPERATURE_PINS temp_pins;
FAN_PINS fan_pins;
TestChoices choices;

void setup() {
  pinMode(fan_pins.CONTROL, OUTPUT);
  pinMode(fan_pins.LED, OUTPUT);
}

void loop() {
  //turnOnFans(fan_pins);
}
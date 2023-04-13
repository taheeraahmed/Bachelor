#include <Arduino.h>
#include <utils.h>
#include <fan.h>

MEMORY_EXTENSION_PINS mem_ext_pins;
TEMPERATURE_PINS temp_pins;
FAN_PINS fan_pins;
TestChoices choices;

void setup() {
  pinMode(fan_pins.CONTROL, OUTPUT);
}

void loop() {
  turnOnFans(fan_pins);
  delay(5000);

  turnOffFans(fan_pins);
  delay(5000);
}
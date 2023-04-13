#include <Arduino.h>
#include <save_temp_to_csv.h>
#include <utils.h>
#include <fan.h>

MEMORY_EXTENSION_PINS mem_ext_pins;
TEMPERATURE_PINS temp_pins;
FAN_PINS fan_pins;
TestChoices choices;
String fileName;

void setup() {
  pinMode(fan_pins.CONTROL, OUTPUT);
  pinMode(fan_pins.LED, OUTPUT);
}

void loop() {
  //turnOnFans(fan_pins);
}

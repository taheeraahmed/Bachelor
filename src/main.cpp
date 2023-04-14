#include <Arduino.h>
#include <save_temp_to_csv.h>
#include <utils.h>
#include <fan.h>

MEMORY_EXTENSION_PINS mem_ext_pins;
TEMPERATURE_PINS temp_pins;
FAN_PINS fan_pins;
TestChoices choices;
String filename;

unsigned long start_time = millis();

void setup() {
  filename = setupReadCSV(mem_ext_pins, start_time, choices);
  pinMode(fan_pins.CONTROL, OUTPUT);
  pinMode(fan_pins.LED, OUTPUT);
}

void loop() {
  readSensorValuesToCsv(temp_pins, filename.c_str());
  //turnOnFans(fan_pins);
}

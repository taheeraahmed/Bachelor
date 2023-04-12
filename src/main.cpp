#include <Arduino.h>
#include <save_temp_to_csv.h>
#include <utils.h>

MEMORY_EXTENSION_PINS memExtPins;
TEMPERATURE_PINS tempPins;
TestChoices choices;
String fileName;

void setup() {
  unsigned long startTime;
  fileName = setupReadCSV(memExtPins, startTime, choices);
}

void loop() {
  readSensorValues(tempPins, fileName.c_str());
}
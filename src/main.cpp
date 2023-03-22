#include <Arduino.h>
#include <save_temp_to_csv.h>
#include <utils.h>

MEMORY_EXTENSION_PINS memExtPins;
// TODO: Set temperature pins (Elise)
TEMPERATURE_PINS tempPins;

// TODO: Define the test choices  (Mina)
TestChoices choices;

String fileName;

void setup() {
  // TODO: Set startTime (Mina)
  unsigned long startTime;

  fileName = setupReadCSV(memExtPins.CS, startTime, choices);
}

void loop() {
  readSensorValues(tempPins, fileName.c_str());
}
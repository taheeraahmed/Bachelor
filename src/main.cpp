#include <Arduino.h>
#include <save_temp_to_csv.h>
#include <utils.h>

MEMORY_EXTENSION_PINS memExtPins;
// TODO: Set temperature pins (Elise)
int TEMP_PIN_1;
int TEMP_PIN_2;
int TEMP_PIN_3;
int TEMP_PIN_4;

// TODO: Define the test choices  (Mina)
testChoices choices;

String fileName;

void setup() {
  // TODO: Set startTime (Mina)
  unsigned long startTime;

  fileName = setupReadCSV(memExtPins.CS, startTime, choices);
}

void loop() {
  readSensorValues(TEMP_PIN_1, TEMP_PIN_2, TEMP_PIN_3, TEMP_PIN_4, fileName.c_str());
}
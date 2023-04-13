#include <Arduino.h>
#include <utils.h>
#include <fan.h>

MEMORY_EXTENSION_PINS mem_ext_pins;
TEMPERATURE_PINS temp_pins;
TestChoices choices;

const int FAN_PIN = 13;
int i = 0;

void setup() {
  pinMode(FAN_PIN, OUTPUT);
}

void loop() {
  int speed = 180;
  analogWrite(FAN_PIN, speed);
  delay(3000);

  speed = 0;
  i = i + 1;
  analogWrite(FAN_PIN, speed);
  delay(3000);
}
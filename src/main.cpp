#include <Arduino.h>
#include <utils.h>
#include <fan.h>
#include <EEPROM.h>

const int LED_PIN = 44;

MEMORY_EXTENSION_PINS mem_ext_pins;
TEMPERATURE_PINS temp_pins;
//FAN_PINS fan_pins;
TestChoices choices;

const int FAN_PIN = 3;
#define FS_ADDR 0x01
int  fanSpeed;

void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);

}

void loop() {
  
}
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
  EEPROM.get(FS_ADDR, fanSpeed);
  if(fanSpeed < 1)  fanSpeed = 255;
  analogWrite(FAN_PIN, fanSpeed);
  Serial.begin(9600);

}
char  rx_byte = 0;
String input = "";

void loop() {
  if (Serial.available()  > 0) {    // is a character available?
    rx_byte = Serial.read();       //  get the character
  
    // check if a number was received
    if ((rx_byte  >= '0') && (rx_byte <= '9')) {
      input.concat(rx_byte);
      
    }
    else if (rx_byte == '\n') {
      Serial.print("Received: ");
      Serial.println(input);
      if(input.toInt() < 256) {
        fanSpeed = input.toInt();
        EEPROM.put(FS_ADDR,  fanSpeed);
      } else {
        Serial.println("Invalid Number");
      }
      input = "";
    }
    else {
      Serial.println("Not  a number.");
    }
  } // end: if (Serial.available() > 0)
  analogWrite(FAN_PIN,  fanSpeed);
}
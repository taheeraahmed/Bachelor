#include <mainFunctions/mainFunctions.h>
#include <Adafruit_I2CDevice.h>
#include <Arduino.h>


void setup(){
  Serial.begin(9600);
  initScreen();
}

void loop(void){
  systemWaiting();
}

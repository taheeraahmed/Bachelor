#include <mainFunctions/mainFunctions.h>
#include <Adafruit_I2CDevice.h>
#include <Arduino.h>


void setup(){
  initPinChangeInterrupt();
  initiateSystem();
}

void loop(void){
  testDataUpdate(2000);
}

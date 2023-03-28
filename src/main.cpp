#include <Arduino.h>

/*
To eksempelkoder som begge får led koblet til pin 38 til å blinke.
Eksempel a bruker Arduino C med 1 sek delay
Eksempel b bruker Embedded C med 500 ms delay
*/

const int LED_PIN = 38;


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_PIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_PIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}

/*
void setup() {
  DDRF = DDRF | B10001100;  //Leds as OUTPUT at Pin 38, 19 & 18
  pin0 = B00000001
}

void loop() {
  PORTF = B10001100;   //Led at Pin 38,19,18 HIGH
  delay(500);         // wait for a second
  
  PORTF = B00000000;  //Leds at Pin 38,19,18 LOW
  delay(500);        // wait for a second
}
*/
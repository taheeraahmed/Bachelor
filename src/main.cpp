#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

const int LED_PIN = 44;
const int TFT_CS = ???;
const int TFT_DC = ???;
const int TFT_MOSI = ???;
const int TFT_SCLK = ???;
const int TFT_RST = ???;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_PIN, OUTPUT);
  Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_PIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                  // wait for a second
  digitalWrite(LED_PIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                  // wait for a second
}
#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

#define used_pins_keypad 0b01111111
#define row_pins 0b00001111
#define col_pins 0b01110000
#define Keypad_DDRx DDRA
#define Keypad_PORTx PORTA
#define Keypad_PINx PINA

/*void init_keypad() {
  Keypad_DDRx &= ~(used_pins_keypad & row_pins); //Setter alle rad pinnene til innsignal og resten til utsignal
  Keypad_DDRx |= (used_pins_keypad & col_pins); // Setter alle kolonne pinnene til utsignal Setter 
  Keypad_PORTx |= (used_pins_keypad & row_pins); //Enabler pull up resistor på alle rad pinnene
}*/

void setup() {
//init_keypad();
Serial.begin(9600);

Keypad_DDRx  |= (1 << 6) | (1 << 5) | (1 << 4);       //kobler kolonnepinnene på A 
Keypad_PORTx |= (1 << 6) | (1 << 5) | (1 << 4);       //kolonnepinnene på PORTA
Keypad_PORTx |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);  //Radpinnene på PORTA
/*
DDRA  |= (1 << 2) | (1 << 4) | (1 << 6);
PORTA |= (1 << 2) | (1 << 4) | (1 << 6);
PORTC |= (1 << 1) | (1 << 3) | (1 << 5) | (1 << 7);*/
}

void loop() {
  PORTA &= ~(1 << 6);
  delay(1);
  if(!(PINA & (1 << 3))){ Serial.print("#\n"); }
  if(!(PINA & (1 << 2))){ Serial.print("9\n"); }
  if(!(PINA & (1 << 1))){ Serial.print("6\n"); }
  if(!(PINA & (1 << 0))){ Serial.print("3\n"); }
  PORTA |= (1 << 6);

  PORTA &= ~(1 << 5);
  delay(1);
  if(!(PINA & (1 << 3))){ Serial.print("0\n"); }
  if(!(PINA & (1 << 2))){ Serial.print("8\n"); }
  if(!(PINA & (1 << 1))){ Serial.print("5\n"); }
  if(!(PINA & (1 << 0))){ Serial.print("2\n"); }
  PORTA |= (1 << 5);

  PORTA &= ~(1 << 4);
  delay(1);
  if(!(PINA & (1 << 3))){ Serial.print("*\n"); }
  if(!(PINA & (1 << 2))){ Serial.print("7\n"); }
  if(!(PINA & (1 << 1))){ Serial.print("4\n"); }
  if(!(PINA & (1 << 0))){ Serial.print("1\n"); }
  PORTA |= (1 << 4);

  delay(150);

}
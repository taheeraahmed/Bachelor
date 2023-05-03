#include "Keypad.h"

void initKeypad(){
    DDRA  |= (1 << 6) | (1 << 5) | (1 << 4);       //kobler kolonnepinnene på A 
    PORTA |= (1 << 6) | (1 << 5) | (1 << 4);       //kolonnepinnene på PORTA
    PORTA |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);  //Radpinnene på PORTA

}

void getKey(){
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
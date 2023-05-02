#include <avr/io.h>
// Enkel funksjon som får Rød og grønn led til å lyse ved knappetrykk.
// Skal kun brukes som referanse for koding av leds og knapp.

void BlinkeLed(){
  DDRG |= (1 << PIN1) | (1 << PIN0);
  DDRL |= (1 << PIN7);
  DDRH &= ~(1 << PIN6);

  while(1){
    if (PINH & (1 << PIN6)){
      PORTG |= (1 << PIN0);
      PORTL &= ~(1 << PIN7);
    }
    else {
      PORTL |= (1 << PIN7);
      PORTG &= ~(1 << PIN0);
    }
  }
}
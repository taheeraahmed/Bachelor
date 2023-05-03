#include "NIR/NIR.h"

/**
 * @brief Function to initiate PWM on timer0. 
 * @details 
 * The function sets the clock frequency to XXX and enables the owerflov vector.
 * Timer0 is used to controll the NIR light and activates PINs xxx on port xxx
*/
void initTimer0(){
  // Setter opp compare Match instillinger for teller 0.
  TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
  TCCR0B |= (1 << CS02);
  // Skrur på interrupt for teller 0.
  TIMSK0 |= (1 << TOIE0);

  //Setter alle pinner som styres av teller 0 til utganger.
  DDRE |= (1 << PIN5) | (1 << PIN4) | (1 << PIN3);
  DDRG |= (1 << PIN5);
  DDRH |= (1 << PIN4) | (1 << PIN3);
}


void setNIR(uint8_t NIRSettings[4],uint8_t NIRDuty, uint8_t R_ID){
  //Arrayene under beskriver egenskapene for de ulike LED hodene.
  // Ved utvidelse for flere led hoder må alle 3 arrayene oppdateres.
  // Led-hode 0 (avkoblet), Led-hode 1, Led-hode2, Led-Hode 3

  for (uint8_t i = 0; i <= arrayLength; i++){
    if (ledRID[i] == R_ID){
      nirData[0] = ledWaveLength[i];
      nirData[1] = R_ID;
      nirData[2] = numEnPins[i];
    }
  }
  OCR0A = NIRDuty;
}

// Setter opp avbuddsvektor for compare C timer 1
ISR(TIMER0_COMPA_vect){
  if (nirData[2] == 1){
    PORTE |= (1 << PIN4);
  }
  else if (nirData[2] == 2){
    PORTE |= (1 << PIN4) | (1 << PIN5);
  }
  else if (nirData[2] == 3){
    PORTE |= (1 << PIN4) | (1 << PIN5);
    PORTG |= (1 << PIN5);
  }
  else if (nirData[2] == 4){
    PORTE |= (1 << PIN5) | (1 << PIN4) | (1 << PIN3);
    PORTG |= (1 << PIN5);
  }
  else if (nirData[2] == 5){
    PORTE |= (1 << PIN5) | (1 << PIN4) | (1 << PIN3);
    PORTG |= (1 << PIN5);
    PORTH |= (1 << PIN3);
  }
  else if (nirData[2] == 6){
    PORTE |= (1 << PIN5) | (1 << PIN4) | (1 << PIN3);
    PORTG |= (1 << PIN5);
    PORTH |= (1 << PIN4) | (1 << PIN3);
  }
  else{
    PORTE &= ~((1 << PIN5) | (1 << PIN4) | (1 << PIN3));
    PORTG &= ~((1 << PIN5));
    PORTH &= ~((1 << PIN4) | (1 << PIN3));
  }
}
// Setter opp avbruddsvektor for overflow på timer 1
ISR(TIMER0_OVF_vect){
  PORTE &= ~((1 << PIN5) | (1 << PIN4) | (1 << PIN3));
  PORTG &= ~((1 << PIN5));
  PORTH &= ~((1 << PIN4) | (1 << PIN3));  
}
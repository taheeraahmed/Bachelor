#include "NIR/NIR.h"

/*
Variabler som lagrer informasjon knyttet til alle LED-hodene som brukes
*/
uint8_t LED_ID[4] = {0, 1, 2, 3};                  // Inneholder ID nummer på vilket hode som blir benyttet.
uint16_t ledRID[4] = {0, 1000, 10000, 51000};      // Inneholder verdien på de ulike identifikasjonsmotstandene.
uint16_t ledWaveLength[4] = {0, 660, 810, 880};    // Inneholder frekvensen på NIR-lyset levert fra hver LED-hode.
uint8_t numEnPins[4] = {0, 1, 3, 3};               // Inneholder antall PWM pinner som brukes for hvert LED-hode.


uint8_t nirData[3];       // Collects all data on the chosen LED-head {ledWaveLength[x], ledRID[x], numEnPins[x]}


/**
 * @brief Function to initiate PWM on timer0. 
 * @details 
 * The function sets the clock prescaler to 256 and enables the owerflov vector.
 * Timer0 is used to controll the NIR light.
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

/**
 * @brief Starts the NIR-light projection
 * @details 
 * The function turns the LED-array which controlls the NIR-light emission
 * Timer0 is used to controll the PWM frequency for the NIR light. 
 * For IC_HG to function it also needs to be enabled by setting the DAC output voltage to 5V
*/
void setNIR(uint8_t NIRDuty, uint8_t R_ID){
  // Sammenlikner R_ID med de ulike instillingene
  for (uint8_t i = 0; i <= 3; i++){
    if (LED_ID[i] == R_ID){
      // nir_data samler all relevant informasjon om LED-hodet som blir benyttet
      nirData[0] = ledWaveLength[i];
      nirData[1] = R_ID;
      nirData[2] = numEnPins[i];
    }
  }

  // Skrur på spenningsforsyning til IC-HG LED-driveren. 
  setDAC(true);
  
  // Omvend PWM der pinnen settes lav fra start og skiftes til høy ved Compare Match.
  // For rett lengde for på signalet må dutyCycle omskrives.
  OCR0A = (255 - NIRDuty);
}

/**
 * @brief Turns NIR-light off by cutting the voltage supply to IC-HG.
*/
void endNIR(void){
  // DAC skrus av som gjør at IC_HG LED-driveren vil gi ut et spenningsnivå på 0V.
  setDAC(false);
}

/**
 * @details 
 * Sets ISR for Compare Match A interrupt on timer 0.
 * Turns the activated pins on.
*/
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


/**
 * @details 
 * Sets ISR for overflow interrupt on timer 0.
 * Turns all pins connected to the EN pins on the IC_HG LED-driver off.
*/
ISR(TIMER0_OVF_vect){
  PORTE &= ~((1 << PIN5) | (1 << PIN4) | (1 << PIN3));
  PORTG &= ~((1 << PIN5));
  PORTH &= ~((1 << PIN4) | (1 << PIN3));  
}
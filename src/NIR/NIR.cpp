#include "NIR/NIR.h"

/*
Variabler som lagrer informasjon knyttet til alle LED-hodene som brukes
Disse bør oppdateres når et nytt LED-hode blir designet.
*/
uint8_t LED_ID[4] = {0, 1, 2, 3};                  // Inneholder ID nummer på vilket hode som blir benyttet.
uint16_t ledRID[4] = {0, 1000, 10000, 51000};      // Inneholder verdien på de ulike identifikasjonsmotstandene.
uint16_t ledWaveLength[4] = {0, 660, 810, 880};    // Inneholder frekvensen på NIR-lyset levert fra hver LED-hode.
uint8_t numEnPins[4] = {0, 1, 3, 3};               // Inneholder antall PWM pinner som brukes for hvert LED-hode.


// Samnler all relevant informasjon om LED-hodet som blir benyttet.
uint8_t nirData[4]; // [0] = ledWaveLength, [1] = ID, [2] = numEnPins, [3] = LED-matrise av/på brukes ved randomisert modus       


/**
 * @brief Function to initiate PWM on timer0. 
 * @details 
 * The function sets the clock prescaler to 256 and enables the owerflov vector.
 * Timer2 is used to controll the NIR light.
*/
void initTimer2(){
  // Setter opp compare Match instillinger for teller 0.
  TCCR2A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
  TCCR2B |= (1 << CS02);

  // Skrur på interrupt for teller 0.
  TIMSK2 |= (1 << TOIE0);

  //Setter alle pinner som styres av teller 0 til utganger.
  DDRE |= (1 << PIN5) | (1 << PIN4) | (1 << PIN3);
  DDRG |= (1 << PIN5);
  DDRH |= (1 << PIN4) | (1 << PIN3);
}

/**
 * @brief Starts the NIR-light projection
 * @details 
 * The function turns the LED-array which controlls the NIR-light emission
 * Timer2 is used to controll the PWM frequency for the NIR light. 
 * For IC_HG to function it also needs to be enabled by setting the DAC output voltage to 5V
 * @param NIRmode The mode of the NIR-light emission. 0 = NIR-light, 1 = Placebo, 2 = Random
 * @param NIRfreq The frequency of the NIR-light emission. 0 = Continuous, 1 = High, 2 = Low
 * @param R_ID The ID of the LED-head used for the NIR-light emission
*/
void startNIR(uint8_t NIRmode, uint8_t NIRfreq, uint8_t R_ID){
  uint8_t NIRDuty;

  // Setter duty cycle ut ifra bruker input
  switch(NIRfreq){
    case 0:     
      NIRDuty = 255;  // Kontinuerlig pulsering med 100% duty cycle
      break;
    case 1:
      NIRDuty = 188;  // Høyfrekvent pulsering med 75% duty cycle
      break;
    case 2:
      NIRDuty = 70;  // Lavfrekvent pulsering med 25% duty cycle
      break;
  }
  for (uint8_t i = 0; i <= 3; i++){
    if (LED_ID[i] == R_ID){
      // NIR_data samler all relevant informasjon om LED-hodet som blir benyttet
      nirData[0] = ledWaveLength[i];
      nirData[1] = R_ID;
      nirData[2] = numEnPins[i];
    }
  }

  // Setter NIR-modus ut ifra bruker input
  switch (NIRmode){
    case 0:
      setDAC(true);           // Modus 0: NIR-belysning
      nirData[3] = 1;
      break;
    case 1:
      setDAC(false);          // Modus 1: Placebo
      nirData[3] = 0;
      break;
    case 2:
      if(rand() % 2 == 0){     // Modus 3: Randomisering
        setDAC(false);
        nirData[3] = 0;
      }
      else{
        setDAC(true);
        nirData[3] = 1;
      }
  }
  
  
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
ISR(TIMER2_COMPA_vect){
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
ISR(TIMER2_OVF_vect){
  PORTE &= ~((1 << PIN5) | (1 << PIN4) | (1 << PIN3));
  PORTG &= ~((1 << PIN5));
  PORTH &= ~((1 << PIN4) | (1 << PIN3));  
}
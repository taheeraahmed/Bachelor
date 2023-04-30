#include "PWM/PWM.h"
#include <avr/interrupt.h>

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
}
/**
 * @brief Function to initiate PWM on timer1. 
 * @details 
 * The function sets the clock frequency to XXX and enables the owerflow vector.
 * Timer1 is used to controll the the fans on the controll unit and the LED-head including the buzzer.
*/
void initTimer1(){
  // Setter opp compare match insillinger for teller 1.
  TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << COM1C1) | (1 << WGM11) | (1 << WGM10);
  TCCR1B |= (1 << CS11) | (1 << CS10);
  // Skrur på interrupt på teller 1.
  TIMSK1 |= (1<< TOIE1);

  DDRB |= ((1 << PIN4) | (1 << PIN5));
  DDRH |= (1 << PIN5);
}

/**
 * @brief Function to turn on/off buzzer and set the duty cycle. 
 * @details 
 * To turn the buzzer on/off, the timer on the compare match A is enabled/disabled.
 * The duty cycle is set by writing to the OCR1A register.
*/
void setBuzzerAlarm(bool buzzerState, uint8_t buzzDuty){
  if (buzzerState == true){
    TIMSK1 |= ((1 << OCIE1A));
  }
  else if(buzzerState == false){
    TIMSK1 &= ~(1 << OCIE1A);
  }
  OCR1A = 65535 - ((65535/255)*buzzDuty); 
}

/**
 * @brief Function to turn on/off fans and set the duty cycle. 
 * @details 
 * To turn the controll fan on/off, the timer on the compare match B is enabled/disabled.
 * The duty cycle is set by writing to the OCR1B register.
 *
 * To turn the led fan on/off, the timer on the compare match C is enabled/disabled.
 * The duty cycle is set by writing to the OCR1C register.
*/
void setFans(bool controllFans, bool ledFans, uint8_t controllFanDuty, uint8_t ledFanDuty){
  if ((ledFans == true) & (controllFans == true)){
    TIMSK1 |= (1 << OCIE1B) | (1 << OCIE1C);
  }
  else if (controllFans == true){
    TIMSK1 |= (1 << OCIE1B);
    TIMSK1 &= ~(1 << OCIE1C);
  }
  else if (ledFans == true){
    TIMSK1 |= (1 << OCIE1C);
    TIMSK1 &= ~(1 << OCIE1B);
  }
  else {
    TIMSK1 &= ~((1 << OCIE1B) | (1 << OCIE1C));
  }
  //OCR1B = controllFanDuty;
  OCR1B = 65535 - ((65535/255)*controllFanDuty);
  OCR1C = 65535 - ((65535/255)*ledFanDuty);
}


void initNIR(uint8_t NIRDuty, uint8_t R_ID){

}

// Setter opp avbuddsvektor for compare A timer 1
ISR(TIMER1_COMPA_vect){
  PORTH |= (1 << PIN5);
}
// Setter opp avbuddsvektor for compare B timer 1
ISR(TIMER1_COMPB_vect){
  PORTB |= (1 << PIN4);
}
// Setter opp avbuddsvektor for compare C timer 1
ISR(TIMER1_COMPC_vect){
  PORTB |= (1 << PIN5);
}
// Setter opp avbruddsvektor for overflow på timer 1
ISR(TIMER1_OVF_vect){
  PORTB &= ~((1 << PIN4) | (1 << PIN5));
  PORTH &= ~(1 << PIN5);
}

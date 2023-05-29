#include "PWM/PWM.h"

// timer variabler for buzzer
unsigned long current_time__buzzer;
unsigned long old_time_buzzer;
bool buzzer_trig;

/**
 * @brief Function to initiate PWM on timer3. 
 * @details 
 * The function sets the clock frequency prescaler to 256 and enables the owerflow vector.
 * Timer3 is used to controll the the fans on the controll unit and the LED-head including the buzzer.
*/
void initTimer3(void){
  // Setter opp compare match insillinger for teller 3.
  TCCR3A |= (1 << COM3A1) | (1 << COM3B1) | (1 << COM3C1) | (1 << WGM31) | (1 << WGM30);
  TCCR3B |= (1 << CS31) | (1 << CS30);
  // Skrur på interrupt på teller 3.
  TIMSK3 |= (1<< TOIE3);

  //Setter alle pinner som styres av teller 3 til utganger.
  DDRB |= ((1 << PIN4) | (1 << PIN5));  
  DDRH |= (1 << PIN5);
}

/**
 * @brief Function to turn on/off buzzer and set the duty cycle. 
 * @details 
 * To turn the buzzer on/off, the timer on the compare match A is enabled/disabled.
 * The duty cycle is set by writing to the OCR1A register.
 * By using the getTime function the buzzer is turned on and off when enabled.
 * @param buzzerState Enables buzzer [0-1]
 * @param buzzDuty Sets the dutyCycle [0-255]
 * @param interval Sets the interval wich the buzzer will be turned on/off [ms]
*/
void setBuzzerAlarm(bool buzzerState, uint8_t buzzDuty, uint16_t interval){
  if (buzzerState == true){

    current_time__buzzer = getTime();

    // Sjekker om 
    if ((current_time__buzzer - old_time_buzzer) > interval){
      if (buzzer_trig == false){
        buzzer_trig = true;
        TIMSK3 |= ((1 << OCIE3A));
      }
      else {
        buzzer_trig = false;
        TIMSK3 &= ~(1 << OCIE3A);
      }
      old_time_buzzer = current_time__buzzer;
      
    }
  }
  else if(buzzerState == false){
    TIMSK3 &= ~(1 << OCIE3A);
  }
  OCR3A = 65535 - ((65535/255)*buzzDuty); 
  sei();
}

/**
 * @brief Function to turn on/off fans and set the duty cycle. 
 * @details 
 * To turn the controll fan on/off, the timer on the compare match B is enabled/disabled.
 * The duty cycle is set by writing to the OCR1B register.
 *
 * To turn the led fan on/off, the timer on the compare match C is enabled/disabled.
 * The duty cycle is set by writing to the OCR1C register.
 * @param [controllFans] Turns fans on controll unit on/off [0-1]
 * @param [ledFans] Turns fans on led-head on/off [0-1]
 * @param [caontrollFanDuty] Sets duty cycle for fans on controll unit [0-255]
 * @param [ledFanDuty] Sets duty cycle for fans on led-head [0-255]
*/
void setFans(bool controllFans, bool ledFans, uint8_t controllFanDuty, uint8_t ledFanDuty){
  if ((ledFans == true) & (controllFans == true)){
    TIMSK3 |= (1 << OCIE3B) | (1 << OCIE3C);
  }
  else if (controllFans == true){
    TIMSK3 |= (1 << OCIE3B);
    TIMSK3 &= ~(1 << OCIE3C);
  }
  else if (ledFans == true){
    TIMSK3 |= (1 << OCIE3C);
    TIMSK3 &= ~(1 << OCIE3B);
  }
  else {
    TIMSK3 &= ~((1 << OCIE3B) | (1 << OCIE3C));
  }
  //OCR1B = controllFanDuty;
  OCR3B = 65535 - ((65535/255)*controllFanDuty);
  OCR3C = 65535 - ((65535/255)*ledFanDuty);
  sei();
}

// Setter opp avbuddsvektor for compare A timer 3
ISR(TIMER3_COMPA_vect){
  // Skrir på PWM 8 pinnen koblet til buzzer.
  PORTH |= (1 << PIN5);
}
// Setter opp avbuddsvektor for compare B timer 3
ISR(TIMER3_COMPB_vect){
  // Skrir på PWM 10 pinnen koblet til viftene på styringsenheten.
  PORTB |= (1 << PIN4);
}
// Setter opp avbuddsvektor for compare C timer 3
ISR(TIMER3_COMPC_vect){
  // Skrir på PWM 11 pinnen koblet til viften på LED-hodet.
  PORTB |= (1 << PIN5);
}
// Setter opp avbruddsvektor for overflow på timer 3
ISR(TIMER3_OVF_vect){
  // Alle pinner blir skrudd av
  PORTB &= ~((1 << PIN4) | (1 << PIN5));
  PORTH &= ~(1 << PIN5);
}
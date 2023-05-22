/*
 * getTime.c
 * 
 * Created: 19.05.2023
 * 
 * Sourced from: https://adnbr.co.uk/articles/counting-milliseconds
 */ 


#define one_millisecond ((F_CPU / 1000) / 8)

#include <avr/io.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
#include "getTime/getTime.h"


volatile unsigned long getTime_timer;

/**
* @brief Et avbrudd som blir kalt hvert millisekund
*
*Avbruddshåndteringen inkrementerer en variabel hvert milisekund
*/
ISR (TIMER1_COMPA_vect)
{
   getTime_timer++;
}

/**
* @brief Initiering av tellefunksjon
*
* Funksjonen setter preskalerer, trigger overflow, 
* setter CTC-modus og skrur på avbrudd.
*/
void initGetTime(void){
    /*CS11 setter timer-inngang delt på 8, WGM12 setter/starter 
    OCR1A clear timer på compare match*/
    /*CTC modus og klokke/8*/
    TCCR1B |= (1 << WGM12) | (1 << CS11); 

    /*Timer1, 16 bit som lagres som to 8 bit i output compare A på timer1*/
    OCR1AH = (one_millisecond >> 8);
    OCR1AL = one_millisecond;

    /*enabler compare match interrupt*/
    TIMSK1 |= (1<< OCIE1A);

    sei();
}

/**
* @brief En funksjon som skriver ut antall millisekund siden oppstart
*
* Funksjonen lagrer millisekund siden oppstart i en variabel
* i en atomic-struktur som starter og stopper avbrudd for å ikke påvirke avlesningen.
*
* @return returnerer antall milisekund mikrokontroller har vært skrudd på
*/
unsigned long getTime (void)
{
    unsigned long getTime_return;

      ATOMIC_BLOCK(ATOMIC_FORCEON) {
        getTime_return = getTime_timer;
    }

    return getTime_return;
}
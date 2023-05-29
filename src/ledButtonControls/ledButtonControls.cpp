#include "ledButtonControls/ledButtonControls.h"
#include "getTime/getTime.h"

unsigned long red_led_blink_new;
unsigned long red_led_blink_old;

unsigned long green_led_blink_new;
unsigned long green_led_blink_old;

const uint16_t blink_delay = 500;


/**
* @brief Initiates all led pins.
*/
void initLedPins(void){
    DDRG |= (1 << PIN0);    // Sets pin 41 as output for red Led
    DDRG |= (1 << PIN1);    // Sets pin 40 as output for test indicator
    DDRL |= (1 << PIN7);    // Sets pin 42 as output for green led
}

/**
* @brief Turns red led on.
*/
void redLedOn(void){
    PORTG |= (1 << PIN0);
}

/**
* @brief Binks red led with interval of 500 ms.
*/
void redLedBlink(void){
    red_led_blink_new = getTime();

    if (red_led_blink_new - red_led_blink_old > blink_delay){
        PORTG ^= (1 << PIN0);
        red_led_blink_old = red_led_blink_new;
    }
}

/**
* @brief Turns red led Off.
*/
void redLedOff(void){
    PORTG &= ~(1 << PIN0);
}

/**
* @brief Turns green led on.
*/
void greenLedOn(void){
    PORTL |= (1 << PIN7);
}

/**
* @brief Binks green led with interval of 500 ms.
*/
void greenLedBlink(void){
    green_led_blink_new = getTime();

    if (green_led_blink_new - green_led_blink_old > blink_delay){
        PORTL ^= (1 << PIN7);
        green_led_blink_old = green_led_blink_new;
    }
}

/**
* @brief Turns green led off.
*/
void greenLedOff(void){
    PORTL &= ~(1 << PIN7);
}

/**
* @brief Turns test indicator led on.
*/
void testIndicatorOn(void){
    PORTG |= (1 << PIN1);
}

/**
* @brief Turns test indicator led off.
*/
void testIndicatorOff(void){
    PORTG &= ~(1 << PIN1);
}

/**
 * @brief Aktiverer avbrudd på den grønne knappen.
 */
void initPinChangeInterrupt(void){
  // Setting  
  DDRJ &= ~(1 << PIN1);
  
  // set up interrupt vector table
  PCICR |= (1 << PIN1); // Enable PCINT for Port J
  PCMSK1 |= (1 << PIN1); // Enable PCINT3 for PORTJ PIN!
}

ISR(PCINT1_vect){
    // Når systemet sover vil trykk på grønn knapp vekke systemet og gå til skjermens forside.    
        SMCR &= ~((1 << PIN2) | (1 << PIN0));
        greenButtonTrigg = true;
}
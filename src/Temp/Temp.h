/*
 * Temp.h
 * 
 * Created: 19.05.2023
 * 
 * Sourced from:
 * William, Elliott. (2014). Make: AVR Programming. Utgiversted: O'Reilly Media.
 */ 

#ifndef Temp_H_
#define Temp_H_

#include <avr/io.h>

extern volatile int temp_value_array[4];

/*Settes høy for temp under 28 grader celsius i ett min.*/
extern volatile int flagg_skin_contact;
/*ADC leses ikke av*/
extern volatile int flagg_error_ADC;
/*Antall ganger (med delay_ADC intervall) temp er under 28 grader*/
extern volatile int threshold_skin_contact;
/*Ulike verdier ulike LED-array, 1=1k Ohm, 2=10k Ohm, 3=51k Ohm*/
extern volatile int ID_NIR_LED;

/**
* @brief Funksjon for å initiere ADC-en.
*/
void initADC(void);

/**
* @brief Funksjon for å initiere de ønskede ADC-inngangene.
*/
void initPort(void);

/**
* @brief Funksjon som leser av en ADC-inngang.
* @param pin_ADC Definerer hvilken inngang som skal leses av.
* @return Returnerer en 10-bit ADC-verdi lagret som 16-bit.
*/
uint16_t readADC(uint8_t pin_ADC);

/**
* @brief Funksjon for å regne om 16-bit ADC-verdien til temperaturverdi.
* @param value_ADC er den 16-bit avlest ADC-verdi som skal behandles.
* @return Funksjonen returnerer temperatur i grader celsius som en float verdi.
*/
float calcADC(uint16_t value_ADC);

/**
* @brief En funksjonen som setter ulike flagg basert på temperatur.
* @return Returnerer et array med de fire temperaturene som er registrert.
*/
void setFlaggADC(void);

/**
* @brief Funksjon for å regne ut motstanden til R_ID for identifikajon av LED-array
*/
void calcLedID (void);

#endif
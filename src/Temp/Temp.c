/*
 * Temp.c
 * 
 * Created: 19.05.2023
 * 
 * Sourced from:
 * William, Elliott. (2014). Make: AVR Programming. Utgiversted: O'Reilly Media.
 */ 

#include <avr/io.h>
#include "Temp/Temp.h"
#include "getTime/getTime.h"
#include "getError/getError.h"

#define R_resistance 10000
#define V_source 5
#define offset 0
#define delay_ADC 5000

/*Om variabel er satt høy må systemet skrues av*/
volatile int flagg_skin_contact;

/*Om flagget er satt kjøres ikke for-løkken*/
volatile int flagg_error_ADC;

/*Variabeler hvor det lagres antall ganger på rad temperatur er oversteget en terskel*/
volatile int threshold_skin_contact;
volatile int threshold_LED;
volatile int threshold_PCB;
volatile int threshold_skin;
volatile int threshold_air;

/*Variabel hvor motstandsverdien til NIR-lyset lagres*/
volatile int ID_NIR_LED;

/*Hvert femte sekund lagres de fem temperaturene i dette arrayet*/
volatile int temp_value_array[4];

/*Tid sist getTime ble lest av*/
unsigned long getTime_since_ADC = 0;

/*voltage_factor er spenningsverdien målt ved temperaturenen 100 grader og 0 grader.*/
const float voltage_factor = 1.88; 

/**
* @brief Funksjon for å initiere ADC-en.
*
* I denne funksjonen settes spenningsreferansen,
* prescaleren og ADC-en slåes på.
*/
void initADC(void)
{
  /*Angir AVCC som spenningsreferanse.*/
  ADMUX |= (1<<REFS0); 

  /*Setter prescaleren til 128 delings-faktor.*/
  ADCSRA |=  (1<<ADPS2) |(1<<ADPS1) | (1<<ADPS0);

  /*Slår på ADC-EN*/
  ADCSRA |= (1<<ADEN);
}

/**
* @brief Funksjon for å initiere de ønskede ADC-inngangene.
*
* Initierer de fem ADC-inngangene. 
* En R_ID og fire temperatursensorer
* De fem er: PIN0=LED_ID, PIN1= LED, PIN2 = PCB, PIN3= SKIN, PIN4= AIR.
*/
void initPort(void)
{
  DDRF &= ~(1<<PIN0) & ~(1<< PIN1) & ~(1<< PIN2) & ~(1<< PIN3) & ~(1<< PIN4);   
}

/**
* @brief Funksjon som leser av en ADC-inngang.
*
* Setter ønsket ingang med parameter pin_ADC.
* Starter så en samtale og venter til den er ferdig.
* Returnerer den avleste verdien.
* 
* @param pin_ADC Definerer hvilken inngang som skal leses av.
* @return Returnerer en 10-bit ADC-verdi lagret som 16-bit.
*/
uint16_t readADC(uint8_t pin_ADC)
{
  /*Setter pin_ADC som inngang*/
  ADMUX |= (pin_ADC); 

  /*Starter en samtale/avlesning*/
  ADCSRA |= (1<<ADSC);

  /*Venter til ADSC-bit er tømt, da er samtalen over*/
  loop_until_bit_is_clear(ADCSRA, ADSC);

  return (ADC);
}

/**
* @brief Funksjon for å regne om 16-bit ADC-verdien til temperaturverdi.
* 
* Tar parameter value_ADC og regner om til spenning.
* Så regnes spenning om til temperatur.
* 
* @param value_ADC er den 16-bit avlest ADC-verdi som skal behandles.
* @return Funksjonen returnerer temperatur i grader celsius som en float verdi.
*/
float calcADC(uint16_t value_ADC)
{
  uint16_t i = value_ADC;

  /*Regner om 16-bit avlest ADC-verdi til spenningsverdi*/
  float voltage_ADC = i * (5.0 / 1023.0); 

  /*Regner om spenningsverdi til temperaturverdi*/
  float temp_ADC = (((voltage_ADC * 100) / voltage_factor) + offset);

  return temp_ADC;
}

/**
* @brief En funksjonen som setter ulike flagg basert på temperatur.
*
* getTime funksjonen kalles for å loope setFlaggADC 
* funksjonen hver 5. sekund med hjelp av if-setning.
* Så kjøres en for-løkke for å lese av alle ADC-inngangene.
* I for-løkken er den en switch case med if-setninger som inkrementerer 
* ulike variabler høye basert på de avleste temperaturene fra ADC-en.
* Til slutt er det flere if-setninger som sjekker hvor lenge tempen har
* vært for høy, for så å sette et varselflagg høyt.
*
* @return Returnerer et array med de fire temperaturene som er registrert.
*/
void setFlaggADC(void)
{
  uint16_t bit_val_ADC;
  float temp_val_ADC;
  flagg_error_ADC = 0; 

  unsigned long getTime_current_ADC = getTime();

  /*If-setning for å kjøre koden hvert 5. sekund som er definert i delay_ADC*/
  if(getTime_current_ADC - getTime_since_ADC > delay_ADC) {
    
    /*For-løkke for å lese av de fire ADC-inngangene*/
    for(int j = 1; j < 5; j++)
      {
        /*leser av ADC*/
        bit_val_ADC = readADC(j);

        /*Regner om ADC-verdien til temperatur*/
        temp_val_ADC = calcADC(bit_val_ADC);

      /*Switch case med ifsetninger for å sjekke om temp er for høy*/
      switch (j)
      {
      /*Om temperaturen er over 85 grader vil threshold inkrementeres, under 85 vil den tømmes*/
      case 1: //PIN1= LED;
        threshold_LED = (temp_val_ADC >= 85) ? threshold_LED + 1: 0;
        break;
      
      case 2: //PIN2 = PCB
        /*Om temperaturen er over 70 grader vil threshold inkrementers, under vil den tømmes*/
        threshold_PCB = (temp_val_ADC >= 70) ? threshold_PCB +1 : 0; 
        break;
      
      case 3: //PIN3= SKIN
        /* Om temperaturen er over 28 grader er hudkontakt oppnådd
        og threshold inkrementeres, under 28 grader vil threshold tømmes */
        threshold_skin_contact = (temp_val_ADC <= 28) ? threshold_skin_contact +1 : 0; 

        /* Om temperaturen er over 43 grader er huden på vei til å bli 
       overopphetet og threshold inkrementeres, under 43 grader vil threshold tømmes */
        threshold_skin = (temp_val_ADC >= 43) ? threshold_skin +1 : 0; 
        break;

      case 4: //PIN3= AIR
        /* Om temperaturen er over 43 grader kan luften overopphetet huden
        og threshold inkrementeres, under 43 grader vil threshold tømmes */
        threshold_air = (temp_val_ADC >= 43) ? threshold_air +1 : 0; 
        break;

      default:
        /*Feil i LED-programm!*/
          flagg_error_ADC = 1; 
      }
        
       /*De fire avleste temperaturene lagres i array*/
       temp_value_array[j-1] = temp_val_ADC;
      }
    
    getTime_since_ADC = getTime_current_ADC;
  }
  /*Om temperatur er over 85 grader i ett minutt settes flagg*/
  get_error[17] = (threshold_LED >= 12) ? 1 : 0; 

  /*Om temp på PCB er over 70 grader i ett minutt settes flagg*/
  get_error[18] = (threshold_PCB >= 12) ? 1 : 0; 

  /*Om temp på hud er over 43 grader i ett halvt minutt settes flagg*/
  get_error[19] = (threshold_skin >= 6) ? 1 : 0;

  /*Om temp i luften mellom LED-array og hud er over 43 grader i ett minutt settes flagg*/
  get_error[20] = (threshold_air >= 12) ? 1 : 0;

  /*Om temp på hud er under 28 grader i ett minutt settes flagg*/
  flagg_skin_contact = (threshold_skin_contact >= 12) ? 1 : 0;
 
}

/**
* @brief Funksjon for å regne ut motstanden til R_ID for identifikajon av LED-array
*
*/
void calcLedID (void)
{
  uint16_t val_LED_ID = readADC(0);
  float voltage_LED_ID = val_LED_ID * (5.0 / 1023.0); 
  float resistanc_LED_ID = R_resistance * ( V_source / voltage_LED_ID - 1);

  /*LED 660nm, resistanse 1k ohm*/
  ID_NIR_LED = (resistanc_LED_ID >= 990 && resistanc_LED_ID <= 1100) ? 1 : 0;  

  /*LED 810nm, resistanse 10k ohm*/
  ID_NIR_LED = (resistanc_LED_ID >= 9900 && resistanc_LED_ID <= 10100) ? 2 : 0; 

  /*LED 880nm, resistanse 51k ohm*/
  ID_NIR_LED = (resistanc_LED_ID >= 50900 && resistanc_LED_ID <= 51100) ? 3 : 0;
}
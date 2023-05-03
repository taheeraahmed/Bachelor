#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include "Temp/Temp.h"

#define R_resistance 10000
#define R_thermistor 1000
#define V_source 5
#define offset 0

volatile uint16_t value_ADC;
const float voltage_factor = 1.88; //voltage_factor er spenningsverdien målt ved temperaturenen 100 grader og 0 grader1.

void initADC(void)
{
  ADMUX |= (1<<REFS0) | (1<<MUX0);
  ADCSRA |=  (1<<ADPS2) |(1<<ADPS1) | (1<<ADPS0);
  ADCSRA |= (1<<ADEN);
}

void initPort(void)
{
  DDRF &= ~(1<<PIN0) & ~(1<< PIN1) & ~(1<< PIN2) & ~(1<< PIN3) & ~(1<< PIN4);    //PIN0=LED_ID, PIN1= LED, PIN2 = PCB, PIN3= SKIN, PIN4= AIR
}

uint16_t readADC(uint8_t pinADC)
{
  ADMUX = (0xf0 & ADMUX) | (pinADC);
  ADCSRA |= (1<<ADSC);
  loop_until_bit_is_clear(ADCSRA, ADSC);
  return (ADC);
}

float calcADC(uint16_t i)
{
  value_ADC = i;
  float voltage_ADC = value_ADC * (5.0 / 1023.0); 
  //float resistance_ADC = R_resistance * ( 1 / ((V_source/voltage_ADC ) - 1));
  float temp_ADC = (((voltage_ADC * 100) / voltage_factor) + offset);
  return temp_ADC;
}

void printADC(void)
{
 uint16_t val_ADC;
    for(int j = 1; j < 5; j++)
      {
        val_ADC = readADC(j);
        Serial.print("Temp");
        Serial.print(j);
        Serial.print(":   ");
        Serial.println(calcADC(val_ADC));
      }
}

void calcLedID (void)
{
  uint16_t val_LED_ID = readADC(0);
  float voltage_LED_ID = val_LED_ID * (5.0 / 1023.0); 
  float resistanc_LED_ID = R_resistance * ( V_source / voltage_LED_ID - 1);

  Serial.print("LED_ID:    ");
  Serial.println(resistanc_LED_ID);
}
#ifndef Temp_H_
#define Temp_H_

#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

/**
* @brief short description*
*/
void initADC(void);

/**
* @brief short description*
*/
void initPort(void);

/**
* @brief short description
* @param pinADC description of parameter x
* @return description of return value
*/
uint16_t readADC(uint8_t pinADC);

/**
* @brief short description
*
* More description
*
* @param x description of parameter x
* @return description of return value
*/
float calcADC(uint16_t i);

/**
* @brief short description
*
* More description
*
* @param x description of parameter x
* @return description of return value
*/
void printADC(void);

/**
* @brief short description
*/
void calcLedID (void);

#endif
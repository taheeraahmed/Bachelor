/*
 * getError.h
 * 
 * Created: 19.05.2023
 */ 

#ifndef getError_H_
#define getError_H_

extern volatile int get_error[4];
extern volatile int write_error[4];

/**
* @brief En funksjon for håndtering av feilmeldinger
*/
void getError(void);

#endif
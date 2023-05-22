/*
 * getError.c
 * 
 * Created: 19.05.2023
 */ 

#include <avr/io.h>

volatile int get_error[4];
volatile int write_error[4];
int j = 0;

/**
* @brief En funksjon for håndtering av feilmeldinger
*
* En for funksjon som kjøres kontinuerlig.
* Den sjekker alle flagg fra feilmeldinger, om
* en er satt høyt brukes en if-setning til å skrive 
* til et array hvilket flagg som er satt.
*/
void getError(void){
    for (int i = 0; i < 4; i++)
    {
        int error_flagg = get_error[i];

        if (error_flagg == 1)
        {
            write_error[j] = j+1;
        }
        
    }
    j=0;
}


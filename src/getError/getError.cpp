/*
 * getError.c
 * 
 * Created: 19.05.2023
 */ 

#include <avr/io.h>

volatile int get_error[26];
volatile int write_error[26];
int j = 1;

/**
* @brief En funksjon for håndtering av feilmeldinger
*
* En for funksjon som kjøres kontinuerlig.
* Den sjekker alle flagg fra feilmeldinger, om
* en er satt høyt brukes en if-setning til å skrive 
* til et array hvilket flagg som er satt.
*/
void getError(void){
    for (int i = 1; i < 26; i++)
    {
        int error_flagg = get_error[i];

        if (error_flagg == 1)
        {
            write_error[j] = i;
            j++;
        }
        
    }
    j=0;
}


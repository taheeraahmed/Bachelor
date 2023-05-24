# Overordnede funksjoner som samler hele prosjektet

## Beskrivelse
Denne koden setter sammen hele systemet og lager oppsett for systemflyten.

## Funksjoner

### void initiateSystem(void);
Denne funksjonen samler alle initieringsfunksjoner for systemet.
Kjøres hver gang systemet vekkes.

### void testDataUpdate(unsigned long testLength);
Funksjoen styrer dataInnsamling under forsøk og inneholder en while-loop som kjøres helt til testtiden er nådd.
Den inneholder også konstant sjekk av feilmeldinger, og skriver disse til .csv om det er dukket opp noen.

### void setSystemSleep(void);
Setter systemet i Power down modus.

### void initPinChangeInterrupt(void);
Aktiverer avbrudd på pinne 14 (PORTJ PIN1). 
Når avbruddet trigges 

### uint8_t getRemainingMinutes(unsigned long start, unsigned long duration);
Funksjonen returnerer gjennværende minutter av forsøket.

### uint8_t getRemainingSeconds(unsigned long start, unsigned long duration);
Funksjonen returnerer gjenværende sekunder av forsøket når hele minutter er fjernet.

### void runSystem(void);


```cpp
#include <Arduino.h>
#include "PWM/PWM.h"

void setup(){
    initSystem();
}

void loop(){
    // Systemet kjøres inn i det uendelige
    runSystem();
}
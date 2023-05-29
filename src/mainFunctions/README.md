# Overordnede funksjoner som samler hele prosjektet

## Beskrivelse
Denne koden setter sammen hele systemet og lager oppsett for systemflyten.

## Funksjoner

### void initiateSystem(void);
Denne funksjonen samler alle initieringsfunksjoner for systemet.
Kjøres hver gang systemet vekkes.

### void testDataUpdate(unsigned long testLength);
Funksjoen er satt opp som et forslag til hvordan dataInnsamling under forsøk kan gjennomføres. Funksjonen inneholder en while-loop som kjøres helt til testtiden er nådd eller det er oppnådd en kritisk feil.
Den inneholder også konstant sjekk av feilmeldinger, og skriver disse til .csv om det er dukket opp noen.

### void setSystemSleep(void);
Setter systemet i Power down modus.

### uint8_t getRemainingMinutes(unsigned long start, unsigned long duration);
Funksjonen returnerer gjennværende minutter av forsøket.

### uint8_t getRemainingSeconds(unsigned long start, unsigned long duration);
Funksjonen returnerer gjenværende sekunder av forsøket når hele minutter er fjernet.

### void runSystem(void);
Forslag for hvordan hele systemflyten kan settes opp. Denne funksjonen er ikke implementer fullstendig enda.

```cpp
#include <Arduino.h>
#include "PWM/PWM.h"

// Slik var det tenkt at main skulle se ut. 
//Systemet må kun initieres og startes, når run system kjøres vil dette være en evig loop som omhandler all logikken til koden.
void setup(){
    initSystem();
}

void loop(){
    // Systemet kjøres inn i det uendelige
    runSystem();
}
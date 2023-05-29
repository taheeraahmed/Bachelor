# Bruk av Timer2 for kontroll av NIR-lys
## Beskrivelse
Denne koden setter opp to funksjoner for å kontrollerer LED-hodene som projekterer NIR-lys.
Koden er kompatibel med ATmega2560 mikrokontroller.

## Funksjoner
Det er totalt tre funksjoner som kontrollerer NIR-lyset.

### void initTimer2();
Setter opp Timer2 med "clock prescaler" satt til 256.
Aktiverer interrupt vektorer:
- TIMER2_COMPA_vect
- TIMER2_OVF_vect

### void initNIR(uint8_t NIRDuty, uint8_t R_ID);
Aktiverer PWM. Det er 3 inngangsparametere som bestemmer hvordan NIR-lyset skal oppføre seg.
- NIRmode: Bestemmer forsøkets modus. 
    0 - NIR-belysning
    1 - Placebo
    2 - Randomisert (dobbeltblindet)
- NIRfreq: Bestemmer NIR-lysets egenskaper
    0 - Kontinuerlig belysning (dutycycle 100%)
    1 - Høyfrekvent belysning (dutyCycle 75%)
    2 - Lavfrekvent beslysning (dutycykle 25%)
- R_ID: Forteller hvilket led-hode som er koblet til og setter riktig antall PWM pinner.
        Informasjon om aktivert LED-hode lagres, og det velges riktig antall PWM pinner som må aktiveres for det gitte LED-hodet.

Funksjonen aktiverer også "IC-HG" LED-driver ved å sette utgangsspenning på DAC til 5V

### void endNIR(void);
Skrur av NIR-lys ved å sette utgangsspenningen på DAC-en til 0V.
Dermed fjernes spenningsforskyningen fra "IC-HG" og det vil ikke leveres spenning til LED-hodet.

## Bruk
Dette er en eksempelkode på hvordan funksjonene kan brukes.

```cpp
#include <Arduino.h>
#include "NIR/NIR.h"

bool NIR = false;

void setup(){
    initTimer2();
}

void loop(){
    if (NIR == true){
        // Skrur på LED-hode 2 med PWM dutyCycle = 75%.
        startNIR(0,1,2);
    }
    else if(NIR == false){
        // Skrur av LED-hode
        endNIR();
    }
}
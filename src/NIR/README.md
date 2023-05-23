# Bruk av Timer2 for kontroll av NIR-lys
## Beskrivelse
Denne koden setter opp to funksjoner for å kontrollerer LED-hodene som projekterer NIR-lys.
Koden er kompatibel med ATmega2560 mikrokontroller.

## Funksjoner
Det er totalt tre funksjoner som gjør kontrollerer NIR-lyset.

### void initTimer2();
Setter opp Timer2 med "clock prescaler" satt til 256.
Aktiverer interrupt vektorer:
- TIMER2_COMPA_vect
- TIMER2_OVF_vect

### void initNIR(uint8_t NIRDuty, uint8_t R_ID);
Aktiverer PWM med dutyCycle = NIRDuty på "Compare Match A"
Informasjon om aktivert LED-hode lagres, og det velges riktig antall PWM pinner som må aktiveres for det gitte LED-hodet.
Aktiverer "IC-HG" LED-driver ved å sette utgangsspenning på DAC til 5V

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
        // Skrur på LED-hode 2 med PWM dutyCycle = 150.
        initNIR(150, 2);
    }
    else if(NIR == false){
        // Skrur av LED-hode
        endNIR();
    }
}
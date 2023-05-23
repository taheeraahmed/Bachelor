# Kontoll av PWM på Timer3
## Beskrivelse
Timer3 kontrollerer PWM tre komponenter:
- Buzzer
- Vifte på styringsenhet
- Vifte på LED-hode

## Funksjoner
Det er totalt 3 funksjoener som kontrollerer komponentene knyttet til timer3.

### void initTimer3(void);
Initsiering av timer 3.
Setter opp 4 avbrudds vektorer:
- TIMER3_COMPA_vect     -    Styrer PWM for buzzer 
- TIMER3_COMPB_vect     -    Styrer PWM for vifter på styringsenhet
- TIMER3_COMPC_vect     -    Styrer PWM for vifte på LED-hodet
- TIMER3_OVF_vect       -    Skrur av alle pinnene

### void setBuzzerAlarm(bool buzzerState, uint8_t buzzDuty, uint16_t interval);
Funksjonen styrer alarmen som skal genereres av buzzeren:
Inngangsvariablene som styrer alarmen er:
- Buzzerstate - bestemmer om alarmen skal være av eller på.
- buzzDuty    - setter dutyCycle for alarmen.
- interval    - Setter intervallet alarmen skal være på/av.

Buzzer er koblet til pinne: PWM8 (PORTH PIN5)

### void setFans(bool controllFans, bool ledFans, uint8_t controllFanDuty, uint8_t ledFanDuty);
Funksjonen gjør det mulig å skru av og på de to viftene om hverandre. 
De fire inngangsvariablene tilsvarer to par som kontrollerer hver av de to viftene:
- controllFans      - Skrur på/av vifter på styringsenhet
- controllFanDuty   - Setter dutyCycle for vifter på styringsenhet

- ledFans           - Skrur på/av vifte på LED-hode
- ledFanDuty        - Setter dutyCycle for vifter på LED-hodet

Viftene på styringsenheten er koblet til pinne: PWM10 (PORTB PIN4)
Viftene på LED-hodet er koblet til pinne: PWM11 (PORTB PIN5)

```cpp
#include <Arduino.h>
#include "PWM/PWM.h"

void setup(){
    initTimer3();
}

void loop(){
    // Skrur på vifte på styringsenhet med dutyCycle 200
    void setFans(true, false, 200, 0);

    // Skrur på alarm med dutyCycle = 170
    // Alarm er på i ettt sekund og så av i ett sekund.
    setBuzzerAlarm(true, 170, 1000);
}
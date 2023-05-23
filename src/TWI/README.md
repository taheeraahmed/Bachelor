# TWI kommunikasjon
## Beskrivelse
Koden setter opp grunnleggende funksjoner for TWI kommunikasjon fra ATmega2560. 
Det implementeres logikk for gjennomføring av hele kommunikasjonsprosessen.

### Funksjoner som starter TWI logikk
#### void TWIStartTx(uint8_t address, uint8_t write_reg, uint8_t write_data);
Oppstart av TWI kommunikasjon med tx-modus.
Om det allerede et en aktiv TWI økt vil dataene settes i køen og startes opp når bussen blir ledig.
#### void TWIStartRx(uint8_t address, uint8_t read_register);
Oppstart av TWI kommunikasjon med rx-modus.
Om det allerede et en aktiv TWI økt vil dataene settes i køen og startes opp når bussen blir ledig.

### Funksjoner for innhenting av data fra slaver
#### RTC
 - void getDate(void);
        Henter ut dato fra RTC.
        Motatt data lagres i den globale variabelen calcDate[3] på formatet [dd,mm,åå]
 - void formatDateToChar(uint8_t dateArray[3]);
        Formaterer dato til en string.
        Resultatet lagres i den globale variabelen dateChar[8] på formatet "dd-mm-åå"

 - void getTimeStamp(void);
        Henter ut tid fra RTC.
        Motatt data lagres i den globale variabelen calcTime[3] på formatet [hh,mm,ss]
 - void formatTimeToChar(uint8_t timeArray[3]);
        Formaterer tid til en string.
        Resultatet lagres i den globale variabelen timeChar[8] på formatet "hh:mm:ss"

 - void formatDateTimeToChar(uint8_t dateArray[3], uint8_t timeArray[3]);
        Formaterer dato og tid til en string.
        Resultatet lagres i den globale variabelen dateTimeChar[17] på formatet "dd-mm-åå hh:mm:ss"

 - void resetRTC(uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year);
        Resetter RTC og oppdater dato og tid.
        Må gjøres hver gang RTC-en har mistet strømtilførsel.

#### Batterivakt
 - void getBatteryState(void);
        Henter ut data om Batteriet.
        Lagres i arrayet batteryState[3]:
            - batteryState[0]   -   Batteriprosent [0-100]
            - batteryState[1]   -   Verdi fra 1-5 for batteri indikator på skjermen [1-5]
            - batteryState[2]   -   Batteriets StateOfHealt [0-100]

#### Digital til Analog konverterer
 - void setDAC(bool on_off);
        Setter utgangsspenningen på DAC.
        Når den skrus på settes 5V ut.
        Når den skrus av settes 0V ut.


```cpp
#include <Arduino.h>
#include "PWM/PWM.h"

void setup(){
    Serial.begin(9600);
    initTWI();
}

void loop(){
    // Oppdaterer dato og tid
    getTimeStamp();
    getDate();

    // Formaterer dato og tid og skriver til serial monitor.
    Serial.println(formatDatTimeToChar(calcDate, calcTime));

    // Henter batteridata og sjekker for lavt batteri.
    getBatteryState();
    if (batteryState[0] < 20){
        Serial.println("Lavt Batteri");
    }

    // Skrur på DAC (5V ut)
    setDAC(true);
}
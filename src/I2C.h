

/*
Plan:
1. Lage funksjon for grunnlegende master egenskaper.
   - Mål: Generere START condition
   - Mål: Generere STOP condition
2. Lage funksjon for å lese av RTC
   - Mål: Teste mottakelse at Dato og tid.
3. Lage funksjon for skrive til DAC
   - Mål: Teste at LED lyser (Må lages jallamekk løsning for dette)
4. Lage funksjon for Battery Babysitter.
   - Finn ut av hvordan dette fungerer senere.
*/

#include <Arduino.h>

const int RTC_Address = B11010001; // RTC er satt opp for avlesning.
//const int ADC_Address =  // ADC adresse er ikke definer enda.
//const int BBS_Address =  // Battery BabySitter adresse er ikke definert enda.

/*
Oversikt over registere som brukes:
TWBR: TWI Bit Rate Register
    - Divisjons faktor for bit rate generator.
    - Bestemmer SCL klokkefrekvens for Master modi.
TWCR: TWI Controll Register 
    - Kontrollerer operasjonen til TWI.
        - Enable TWI
        - START Condition
        - Reciever Acknowledge
        - STOP Condition
TWSR: TWI Status Register
TWDR: TWI Data Register
    - Transmit mode: Innholder neste bit som skal sendes.
    - Recieve mode: Inneholder siste bit som ble sendt.
*/


// Funksjon for å sette klokkehastigheten på SCL:
void init_SCL(){
}


// Void funksjon som sender x antall bytes via I2C.
// NB!! Ikke Testet
void I2C_TX(uint8_t address_byte, char transmit_data[]){
  size_t transmit_size = sizeof(transmit_data);
  
  // Setter START Condition ved å skrive til TWCR:
  TWCR = B10100101;
  
  while (TWSR != 0x08){
  }
  TWDR = address_byte;
  TWCR = B10000101;

  if (TWSR == 0x18){
    //Det er opprettet connection med slave. Nå skal data sendes:
    int i = 0;
    while (i <= transmit_size){
      TWDR = transmit_data[i];
      i += 1;
      TWCR = B10100101;
    }
  }
  // Genererer STOP condition:
  TWCR = B10010101;
}


// Funksjon som tar inn data via I2C 
//NB!!! Ikke ferdig.
char I2C_RX(uint8_t address_byte, uint8_t recieve_addr){
  char recieved_data;
  
  // Setter START condition:
  TWCR = B10100101;

  while (TWSR != 0x08){
  }
  TWDR = address_byte;
  TWCR = B10000101;

  if (TWSR == 0x40){
    if (TWINT == 1){

    }
  }
  return recieved_data;
}

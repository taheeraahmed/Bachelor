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

//Funksjonsdefinisjoner:
void init_SCL();
void I2C_TX(uint8_t address_byte, char transmit_data[]);
char I2C_RX(uint8_t address_byte, uint8_t recieve_addr);

unsigned long f_cpu = 16000000L;

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

void setup(){
    Serial.begin(9600);
    //Setter opp SCL og SDA.
    DDRD = PIN1 | PIN0;

    init_SCL(100000);
}

void loop(){
    
  uint8_t data = I2C_RX(RTC_Address, 1);
  Serial.println("wohho");
  delay(1000);
}


// Funksjon for å sette klokkehastigheten på SCL:
// F_SCL kan settes til 100000
void init_SCL(unsigned long F_SCL){
    //Pinne 7 i Registeret PRR0 må settes til 0.
    uint8_t PRR0_Old = PRR0;
    PRR0 = PRR0_Old & ~(1 >> 7);

    // Bruker ønsket F_SCL og setter TWBR:
    uint8_t TWPS_scales[] = {1, 4, 16, 64};
    uint8_t TWPS_Calculated = TWPS_scales[TWSR & 0b00000011];

    // Beregner instillinger til TWBR og skriver til registeret.
    TWBR = (uint8_t)((f_cpu/F_SCL)-16)/(2*(4*exp(TWPS_Calculated)));
}


// Void funksjon som sender x antall bytes via I2C.
// NB!! Ikke Testet
void I2C_TX(uint8_t address_byte, char transmit_data[]){
  size_t transmit_size = sizeof(transmit_data);
  
  // Setter START Condition ved å skrive til TWCR:
  // TWCR = 1X10X10X
  TWCR = (TWINT | TWSTA | TWEN) & ~(1 >> 4) & ~(1 >> 1);
  
  while (TWSR != 0x08){
  }
  TWDR = address_byte;
  // TWCR = 1X00X10X
  TWCR = (TWINT | TWEN) & ~(1 >> 5) & ~(1 >> 4) & ~(1 >> 1);

  if (TWSR == 0x18){
    //Det er opprettet connection med slave. Nå skal data sendes:
    int i = 0;
    while (i <= transmit_size){
      TWDR = transmit_data[i];
      i += 1;
      // TWCR = 1X00X10X
      TWCR = (TWINT | TWEN) & ~(1 >> 5) & ~(1 >> 4) & ~(1 >> 1);
    }
  }
  // Genererer STOP condition:
  // TWCR = 1X01X10X
  TWCR = (TWINT | TWSTO | TWEN) & ~(1 >> 5) & ~(1 >> 1);
}


// Funksjon som tar inn data via I2C 
//NB!!! Ikke ferdig.
char I2C_RX(uint8_t address_byte, uint8_t recieve_addr){
  char recieved_data;
  
   // Setter START Condition ved å skrive til TWCR:
  // TWCR = 1X10X10X
  TWCR = (TWINT | TWSTA | TWEN) & ~(1 >> 4) & ~(1 >> 1);
  
  while (TWSR != 0x08){
  }
  TWDR = address_byte;
  // TWCR = 1X00X10X
  TWCR = (TWINT | TWEN) & ~(1 >> 5) & ~(1 >> 4) & ~(1 >> 1);
  
  uint8_t TWDR_Old = TWDR;
  if (TWSR == 0x40){
    while (TWINT == 1 && TWDR_Old == TWDR){
    }
    recieved_data = TWDR;
  }
  // Genererer STOP condition:
  // TWCR = 1X01X10X
  TWCR = (TWINT | TWSTO | TWEN) & ~(1 >> 5) & ~(1 >> 1);

  return recieved_data;
}

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

/*
Kilder brukt for denne koden:
ATmega2560 Datablad
https://mansfield-devine.com/speculatrix/2018/02/avr-basics-using-the-i2c-bus-1-clock-speed/
*/

#include <avr/io.h>
#include <stdio.h>
#include <util/twi.h>
//#include <cmath>

#include "I2C.h"

unsigned long f_cpu = 16000000UL;

#define RTC_Address 0b11010000 // RTC er satt opp for avlesning.
#define DAC_Address 0b11001100 // Adresse til DAC
//#define BBS_Address =  // Battery BabySitter adresse er ikke definert enda.
char data_to_dac[] = "0011001100110011";
uint8_t data = 0b00000000;

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


uint8_t mainI2C(void){
  
  initI2C(100000);

  I2CTx(DAC_Address, data_to_dac);

  data = I2CRx(RTC_Address, 0x04);
  //Serial.println(data);
  uint8_t Dato = ((data >> 7) & ((1 << PIN1) | (1 << PIN0)))*10+ (data & ((1 << PIN3) | (1 << PIN2) | (1 << PIN1) | (1 << PIN0)));
  printf("Dato:     %d\n", Dato);
  //printf(Dato);

  data = I2CRx(RTC_Address, 0x05);
  //Serial.println(data);
  uint8_t Maned = (data >> 4)*10 + (data & ((1 << 3) | (1 << 2) | (1 << 1) | (1 << 0)));
  printf("Måned:    %d\n", Maned);
  
  data = I2CRx(RTC_Address, 0x06);
  //Serial.println(data);
  uint8_t Ar = (data & ((1 << PIN7) | (1 << PIN6) | (1 << PIN5) | (1 << PIN4)))*10 + (data & ((1 << PIN3) | (1 << PIN2) | (1 << PIN1) | (1 << PIN0)));
  printf("År:    %d\n", Ar);

  return(Ar);
}


// Funksjon for å sette klokkehastigheten på SCL:
// F_SCL kan settes til 100000
/*void TWIInit(void) { 
TWSR = 0x00; TWBR = 0x0C; 
//enable TWI 
TWCR = (1<<TWEN); }*/
void initI2C(unsigned long F_SCL){
    // Setter opp SDA og SCL
    DDRD |= PIN1 | PIN0;
    PORTC |= (1 << PIN1) | (1 << PIN0);
    
    //Nullstiller registerene som skal brukes.
    TWSR = 0x00; 
    TWBR = 0x0C; 
    //enable TWI 
    TWCR = (1<<TWEN); 
    
    //Pinne 7 i Registeret PRR0 må settes til 0.
    uint8_t PRR0_Old = PRR0;
    PRR0 = PRR0_Old & ~(1 << 7);
    
    // Bruker ønsket F_SCL og setter TWBR:
    uint8_t TWPS_scales[] = {1, 4, 16, 64};
    uint8_t TWPS_Calculated = TWPS_scales[TWSR & 0b00000011];
    TWSR = 0b00000011;
    
    // Beregner instillinger til TWBR og skriver til registeret.
    //TWBR = (uint8_t)((f_cpu/F_SCL)-16)/(2*(4*exp(TWPS_Calculated)));
    // Enabler I2C på pinnene.
    TWCR = (1 << TWEN); 
    WaitForAck();
    TWCR = (1 << TWINT);
    WaitForAck();
}

uint8_t checkTWSR(){
    uint8_t status_code;

    status_code = TWSR & ~((1 << PIN2) | (1 << PIN2) | (1 << PIN0));
    return status_code;
}

// Void funksjon som sender x antall bytes via I2C.
// NB!! Ikke Testet
void I2CTx(uint8_t address_byte, char transmit_data[]){
  
  I2CStartCond();
  // Sender adresse til slave:
  I2CWrite(address_byte);
  //Det er opprettet connection med slave. Nå skal data sendes:
  I2CTransmitByte(transmit_data);
  I2CStopCond();
}


// Funksjon som tar inn data via I2C 
//NB!!! Ikke ferdig.
uint8_t I2CRx(uint8_t address_byte, uint8_t register_to_read){
  uint8_t recieved_data;
  
  I2CStartCond();
  // Sender adresse til slave:
  I2CWrite(address_byte); 
  // Sender registeret det skal leses fra hos slave:
  I2CWrite(register_to_read);
  // Sender ny start condition.
  I2CStartCond();
  // Sender adresse til slave med read bit aktivert:
  I2CWrite(address_byte + 1);
  recieved_data = I2CRecieveWithNack();
  I2CStopCond();

  return recieved_data;
}

void I2CStartCond(){
  // Setter START Condition ved å skrive til TWCR:
  TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWSTA));  // TWCR = 1X10X10X
  WaitForAck();
}

void I2CStopCond(){
  // Genererer STOP condition:
  TWCR |= ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));    // TWCR = 1X01X10X
}

void I2CWrite(uint8_t data){
  TWDR = data;
  TWCR = ((1 << TWINT) | (1 << TWEN));  // TWCR = 1X00X10X
  WaitForAck();
}

void I2CTransmitByte(char* data_to_send){
  size_t transmit_size = sizeof(data_to_send);

  for (uint8_t i = 0; i < transmit_size; i++){
    TWDR = data_to_send[i];
    TWCR = ((1 << TWINT) | (1 << TWEN));    // TWCR = 1X00X10X
    WaitForAck();
  }
}

uint8_t I2CRecieveWithAck(){
  TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWEA));
  WaitForAck();
  return TWDR;
}

uint8_t I2CRecieveWithNack(){
  TWCR = ((1 << TWINT) | (1 << TWEN));
  WaitForAck();
  return TWDR;
}

void WaitForAck(){
  while (!(TWCR & (1 << TWINT)));
}

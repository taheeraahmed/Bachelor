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

#include <Arduino.h>

//Funksjonsdefinisjoner:
void init_SCL(unsigned long F_SCL);
void I2C_TX(uint8_t address_byte, char transmit_data[]);
uint16_t I2C_RX(uint8_t address_byte, uint8_t recieve_addr);

#define wait_for_ack while ( !(TWCR & (1 << TWINT)));
unsigned long f_cpu = 16000000L;

const int RTC_Address = 0b11010000; // RTC er satt opp for avlesning.
//const int ADC_Address =  // ADC adresse er ikke definer enda.
//const int BBS_Address =  // Battery BabySitter adresse er ikke definert enda.

uint16_t data = 0b0000000000000000;

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
    Serial.println("1");
    init_SCL(100000);
    Serial.println("2");
}

void loop(){
    
  data = I2C_RX(RTC_Address, 0x05);
  Serial.println(data);
  delay(2000);

  data = I2C_RX(RTC_Address, 0x04);
  Serial.println(data);
  delay(2000);
}


// Funksjon for å sette klokkehastigheten på SCL:
// F_SCL kan settes til 100000
void init_SCL(unsigned long F_SCL){
    //Pinne 7 i Registeret PRR0 må settes til 0.
    Serial.println("3");
    uint8_t PRR0_Old = PRR0;
    PRR0 = PRR0_Old & ~(1 >> 7);
    
    Serial.println("4");
    // Bruker ønsket F_SCL og setter TWBR:
    uint8_t TWPS_scales[] = {1, 4, 16, 64};
    uint8_t TWPS_Calculated = TWPS_scales[TWSR & 0b00000011];
    Serial.println("5");

    // Beregner instillinger til TWBR og skriver til registeret.
    TWBR = (uint8_t)((f_cpu/F_SCL)-16)/(2*(4*exp(TWPS_Calculated)));

    // Enabler I2C på pinnene.
    TWCR = TWEN;
    wait_for_ack;
    TWCR = TWINT;
    wait_for_ack;
}


// Void funksjon som sender x antall bytes via I2C.
// NB!! Ikke Testet
void I2C_TX(uint8_t address_byte, char transmit_data[]){
  size_t transmit_size = sizeof(transmit_data);
  
  // Setter START Condition ved å skrive til TWCR:
  TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWSTA));  // TWCR = 1X10X10X
  wait_for_ack;
  
  // Sender adresse til slave:
  TWDR = address_byte;
  TWCR = (1 << TWINT) | (1 << TWEN);  // TWCR = 1X00X10X
  wait_for_ack;

  //Det er opprettet connection med slave. Nå skal data sendes:
  int i = 0;
  while (i <= transmit_size){
    TWDR = transmit_data[i];
    i += 1;
    // TWCR = 1X00X10X
    TWCR = (1 << TWINT) | (1 << TWEN);
    wait_for_ack;
  }
  
  // Genererer STOP condition:
  // TWCR = 1X01X10X
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
  wait_for_ack;
}


// Funksjon som tar inn data via I2C 
//NB!!! Ikke ferdig.
uint16_t I2C_RX(uint8_t address_byte, uint8_t register_to_read){
  uint16_t recieved_data;
  // Setter START Condition ved å skrive til TWCR:
  TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWSTA));  // TWCR = 1X10X10X
  wait_for_ack;
  Serial.println("x1");

  // Sender "write" adresse til slave:
  TWDR = address_byte;
  TWCR = (1 << TWINT) | (1 << TWEN);  // TWCR = 1X00X10X
  wait_for_ack;
  Serial.println("x2");

  // Sender registeret det skal leses fra hos slave:
  TWDR = register_to_read;
  TWCR = (1 << TWINT) | (1 << TWEN);  // TWCR = 1X00X10X
  wait_for_ack;
  Serial.println("x3");

  // Ny START Condition:
  TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWSTA));  // TWCR = 1X10X10X
  wait_for_ack;
  Serial.println("x4");
  // Bytter over til read:
  TWDR = address_byte + 1;
  TWCR = (1 << TWINT) | (1 << TWEN);  // TWCR = 1X00X10X
  wait_for_ack;
  Serial.println("x5");

  //Mottar data fra slave:
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
  wait_for_ack;
  Serial.println("x6");
  recieved_data = (TWDR << 8);
  TWCR = (1 << TWINT) | (1 << TWEN);  // TWCR = 1X00X10X
  wait_for_ack;
  Serial.println("x7");
  recieved_data += TWDR;
  // Genererer STOP condition:
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);  // TWCR = 1X01X10X
  wait_for_ack;

  Serial.println("Data mottat");

  return recieved_data;
}

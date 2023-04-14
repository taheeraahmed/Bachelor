
#include <avr/io.h>
#include <stdio.h>
#include <util/twi.h>

//Funksjonsdefinisjoner:
uint8_t mainI2C(void);
void initI2C(unsigned long F_SCL);
uint8_t checkTWSR();
void I2CTx(uint8_t address_byte, char transmit_data[]);
uint8_t I2CRx(uint8_t address_byte, uint8_t recieve_addr);
void I2CStartCond();
void I2CStopCond();
void I2CWrite(uint8_t data);
void I2CTransmitByte(char* data_to_send);
uint8_t I2CRecieveWithAck();
uint8_t I2CRecieveWithNack();
void WaitForAck();


#include <Arduino.h>
#include <stdio.h>
#include <util/twi.h>

//Funksjonsdefinisjoner:
void mainI2C();
void init_I2C(unsigned long F_SCL);
uint8_t check_TWSR();
void I2C_TX(uint8_t address_byte, char transmit_data[]);
uint8_t I2C_RX(uint8_t address_byte, uint8_t recieve_addr);
void I2C_START_COND();
void I2C_STOP_COND();
void I2C_WRITE(uint8_t data);
void I2C_TRANSMIT_BYTE(char* data_to_send);
uint8_t I2C_RECIEVE_WITH_ACK();
uint8_t I2C_RECIEVE_WITH_NACK();
void wait_for_ack();

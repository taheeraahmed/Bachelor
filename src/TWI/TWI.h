
#include <avr/io.h>

//Funksjonsdefinisjoner:
void initTWI(unsigned long F_SCL);
void TWIStartTx(uint8_t address, uint8_t write_reg, uint8_t write_data);
void TWIStartRx(uint8_t address, uint8_t read_register);
void TWIStartCond(void);
void TWIWrite(uint8_t data);
uint8_t TWIRecieveWithAck(void);

uint8_t *getDate(void);
uint8_t *getTimeStamp(void);
void resetADC(uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year);

uint16_t getBatteryState(void);
void setDAC(bool on_off);

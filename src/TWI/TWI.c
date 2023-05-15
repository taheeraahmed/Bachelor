
/*
Kilder brukt for denne koden:
ATmega2560 Datablad
https://mansfield-devine.com/speculatrix/2018/02/avr-basics-using-the-i2c-bus-1-clock-speed/
https://github.com/arduino/ArduinoCore-avr/blob/master/libraries/Wire/src/utility/twi.c
*/

#include "TWI/TWI.h"

#define f_cpu 16000000 // Definerer cpu klokke frekvensen.

//Addresser for ulike komponenter koblet til TWI bussen.
#define RTC_Address 0b11010000 // RTC er satt opp for avlesning.
#define DAC_Address 0b11001100 // Adresse til DAC.
#define BBS_Address 0b10101010 // Batteri vakt.

// Variabler som må settes før TWI kommunikasjon kan initiereres.
volatile uint8_t address_byte;
volatile uint8_t register_to_read;
volatile uint8_t transmit_data;

// Globale varialbler som innholder returrn veridiene for getDate og getTimeStamp.
uint8_t calcDate[3];
uint8_t calcTime[3];
uint8_t batteryState[2];


volatile uint8_t data_flag = 0;      //Flag som settes når data overføring er fullført.
volatile bool TWI_ongoing = false;   // Forteller om det er en pågående data overføring på gang.
volatile uint8_t TWI_case = 0;       // Inneholder infor om hvilken state som er neste.
volatile uint8_t TWI_state = 0;      // Foterller om det er pågående en tx eller rx operasjon.
volatile uint8_t TWI_queue[39];      // Array som lagrer 40 bytes med data. Dette tilvarer 10 elementer i køen.

/**
 * @brief Function to initiate TWI. 
 * @details 
 * The function sets all registers nneded to enable the TWI protocoll.
 * The clock frequency on SCL is set to F_SCL.
 * The ports for SCL and SDA is set up as outputs.
 * @param[F_SCL] The desired frequency for the SCL clock.
*/
void initTWI(void){
    //Pinne 7 i Registeret PRR0 må settes til 0.
    PRR0 &= ~(1 << PIN7);
  
    // Setter opp SDA og SCL.
    DDRB |= (1 << PIN7);
    DDRD |= (1<<PIN1) | (1<<PIN0);
    PORTD |= (1 << PIN1) | (1 << PIN0);
    PORTB |= (1<<PIN7);
    
    // Bruker ønsket F_SCL og setter TWBR:
    TWSR &= ~((1<<PIN1)|(1<<PIN0));
    uint8_t TWPS_scales[] = {1, 4, 16, 64};
    uint8_t TWPS_Calculated = TWPS_scales[(TWSR & ((1<<PIN1)|(1<<PIN0)))];
    
    // Beregner instillinger til TWBR og skriver til registeret.
    TWBR = (uint8_t)(((f_cpu / 100000)-16)/(2*TWPS_Calculated));
    
    // Enabler I2C på pinnene.
    TWCR |= (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
    sei();

}
/////////////// GÅOVER SENENRE!!!!
uint8_t checkTWSR(){
    uint8_t status_code;

    status_code = TWSR & ~((1 << PIN2) | (1 << PIN2) | (1 << PIN0));
    return status_code;
}


/**
 * @brief Function to set the start condition for TWI.
 * @details
 * By setting TWSTA high in the TWCR register the TWI communication is initiated.
*/
void TWIStartCond(void){
  // Setter START Condition ved å skrive til TWCR:
  TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWSTA) | (1 << TWIE));  // TWCR = 1X10X10X
}

/**
 * @brief Function to set the stop condition for TWI.
 * @details
 * By setting TWSTO high in the TWCR register the TWI communication is ended.
*/
void TWIStopCond(void){
  // Genererer STOP condition:
  TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWSTO) | (1 << TWIE));    // TWCR = 1X01X10X
}

/**
 * @brief Function to send data to the slave.
 * @details
 * By writing the data we want to send in the TWDR register 
 * and setting TWINT high in TWCR a byte is sent to the slave.
 * @param[data] A data byte to send to the slave.
*/
void TWIWrite(uint8_t data){
  TWDR = data;
  TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWIE));
}

/**
 * @brief Function to recieve data and send acknowledge.
 * @details
 * When data is recieved in the TWDR register and send acknowledge bit.
 * @return Returns the recieved byte in TWDR.
*/
uint8_t TWIRecieveWithAck(void){
  TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWEA) | (1 << TWIE));
  return TWDR;
}

/**
 * @brief Function to recieve data without sending acknowledge.
 * @details
 * When data is recieved in the TWDR register.
 * @return Returns the recieved byte in TWDR.
*/
uint8_t TWIRecieveWithNack(void){
  TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWIE));
  return TWDR;
}



/**
 * @brief Function to start TWI data transmition. 
 * @details 
 * The function checks if there is already an ogoing TWI operation.
 * If this is the case the transmitiondata is stored int the queue.
 * If the TWI buss is free the a statemachine is triggered wich will run independently by interrupts.
 * @param[address] The TWI adress for the module to communicate with.
 * @param[write_reg] The register to write data to on the slave.
 * @param[write_data] Tha data we want to send over to the slave.
*/
void TWIStartTx(uint8_t address, uint8_t write_reg, uint8_t write_data){
  
  if (TWI_ongoing == false){
    address_byte = address;
    register_to_read = write_reg;
    transmit_data = write_data;

    TWI_state = 1;
    TWI_case = 1;
    TWI_ongoing = true;
    TWIStartCond();
    
  }
  else if (TWI_ongoing == true){
    uint8_t i = 0;
    while (1){
      if (TWI_queue[i] == 0){
        TWI_queue[i] = 1;
        TWI_queue[i+1] = address;
        TWI_queue[i+2] = write_reg;
        TWI_queue[i+3] = write_data;

        break;
      }
      else {
        i += 4;
      }
    }
  }
}


/**
 * @brief Function to start TWI data request. 
 * @details 
 * The function checks if there is already an ogoing TWI operation.
 * If this is the case the transmitiondata is stored int the queue.
 * If the TWI buss is free the a statemachine is triggered wich will run independently by interrupts.
 * @param[address] The TWI adress for the module to communicate with.
 * @param[write_reg] The register to write data to on the slave.
*/
void TWIStartRx(uint8_t address, uint8_t read_register){
  
  if (TWI_ongoing == false){

    address_byte = address;
    register_to_read = read_register;

    TWI_state = 2;
    TWI_case = 1;
    TWI_ongoing = true;
    
    TWIStartCond();
  }
  else if (TWI_ongoing == true){
    uint8_t i = 0;
    while (1){
      if (TWI_queue[i] == 0){
        TWI_queue[i] = 2;
        TWI_queue[i+1] = address;
        TWI_queue[i+2] = read_register;
        
        break;
      }
      else {
        i += 4;
      }
    }
  }
}


/**
 * @brief Function recieve raw Date and convert to decimal.
 * @details
 * First the registers 0x04, 0x05, 0x06 is read from and saved in the array rawDate.
 * Then the rawDate is converted to the date in decimal and saved in the array calckDate.
 * @return [calcDate[0]] Returns the date
 * @return [calcDate[1]] Returns the month
 * @return [calcDate[2]] Returns the year
*/
uint8_t *getDate(void){
  uint8_t rawDate[3];

  uint8_t i = 0;  
  while(i == 0){  

    if (data_flag == 0){
      rawDate[0] = 0; 
      rawDate[1] = 0;
      rawDate[2] = 0;
      data_flag = 1;
   
      TWIStartRx(RTC_Address, 0x04); // Henter dato
    }
    else if(data_flag == 2){
      data_flag = 3;
      rawDate[0] = TWDR;
      TWIStartRx(RTC_Address, 0x05); // Henter måneder
    }
    else if(data_flag == 4){
      data_flag = 5; 
      rawDate[1] = TWDR;
      TWIStartRx(RTC_Address, 0x06); // Henter år
    }
    else if(data_flag == 6){ 
      rawDate[2] = TWDR;
      data_flag = 0;
      i = 1;
    }
  }

  calcDate[0] = ((rawDate[0] >> 4) & 0x0F)*10 + (rawDate[0] & 0x0F);  // Beregner dato
  calcDate[1] = ((rawDate[1] >> 4) & 0x0F)*10 + (rawDate[1] & 0x0F);  // Beregner måned
  calcDate[2] = ((rawDate[2] >> 4) & 0x0F)*10 + (rawDate[2] & 0x0F);  // Beregner år

  return calcDate;
}

/**
 * @brief Function recieve raw time and convert to decimal.
 * @details
 * First the registers 0x00, 0x01, 0x02 is read from and saved in the array rawTime.
 * Then the rawTime is converted to the time in decimal and saved in the array calcTime.
 * @return [calcDate[0]] Returns seconds
 * @return [calcDate[1]] Returns minutes
 * @return [calcDate[2]] Returns months
*/
uint8_t *getTimeStamp(void){
  uint8_t rawTime[3];

  uint8_t i = 0;  
  while(i == 0){  
    
    if (data_flag == 0){
      rawTime[0] = 0; 
      rawTime[1] = 0;
      rawTime[2] = 0;
      data_flag = 1;
   
      TWIStartRx(RTC_Address, 0x00); // Henter sekunder
    }
    else if(data_flag == 2){
      data_flag += 1;
      rawTime[0] = TWDR;
      TWIStartRx(RTC_Address, 0x01); // Henter minutter
    }
    else if(data_flag == 4){
      data_flag += 1;
      rawTime[1] = TWDR;
      TWIStartRx(RTC_Address, 0x02); // Henter timer
    }
    else if(data_flag == 6){ 
      rawTime[2] = TWDR;
      data_flag = 0;
      i = 1;
    } 
  }

  calcTime[0] = ((rawTime[0] >> 4) & 0x07)*10 + (rawTime[0] & 0x0F);  // Beregner sekunder
  calcTime[1] = ((rawTime[1] >> 4) & 0x07)*10 + (rawTime[1] & 0x0F);  // Beregner minutter
  calcTime[2] = ((rawTime[2] >> 4) & 0x03)*10 + (rawTime[2] & 0x0F);  // Beregner timer

  return calcTime; 
}

/**
 * @brief Function to reset the RTC by updating the time and date.
 * @details
 * The funcion converts the decimal inputs to binary coded decimal format.
 * Then each value is written to the respective register on the RTC.
 * @param [sec] Sets the seconds [0-59]
 * @param [min] Sets the minutes [0-59]
 * @param [hour] Sets the hours [0-23]
 * @param [date] Sets the date [0-31]
 * @param [month] Sets the month [0-12]
 * @param [year] Sets the year [0-99]
*/
void resetADC(uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year){
  
  uint8_t calcSec = ((sec / 10) << 4) | (sec % 10);
  uint8_t calcMin = ((min / 10) << 4) | (min % 10);
  uint8_t calcHour = ((hour / 10) << 4) | (hour % 10);
  
  uint8_t calcDate = ((date / 10) << 4) | (date % 10);
  uint8_t calcMonth = ((month / 10) << 4) | (month % 10);
  uint8_t calcYear = ((year / 10) << 4) | (year % 10);
  
  uint8_t i = 0;
  while (i == 0){
    if (data_flag == 0){ 
      data_flag = 1;
      TWIStartTx(RTC_Address, 0x00, calcSec);
    }
    else if (data_flag == 2){
      data_flag = 3;
      TWIStartTx(RTC_Address, 0x01, calcMin);
    }
    else if (data_flag == 4){
      data_flag = 5;
      TWIStartTx(RTC_Address, 0x02, calcHour);
    }
    else if (data_flag == 6){
      data_flag = 7;
      TWIStartTx(RTC_Address, 0x04, calcDate);
    }
    else if (data_flag == 8){
      data_flag = 9;
      TWIStartTx(RTC_Address, 0x05, calcMonth);
    }
    else if (data_flag == 10){
      data_flag = 11;
      TWIStartTx(RTC_Address, 0x06, calcYear);
      i = 1;
    }
  }
}


/**
 * @brief Retrieve the current battery perzentage
 * @details
 * Reads from the registers 0x1C and 0x1D to get the battery value in the interval 0x0000 - 0xFFFF
 * Calculates the percentage.
 * @return [batteryCharge] Battery percentage [0 - 100]
*/
uint8_t *getBatteryState(void){
  data_flag = 0;
  uint8_t batteryBytes[4];

  uint8_t i = 0;  
  while(i == 0){  
    
    if (data_flag == 0){
      data_flag = 1;
   
      TWIStartRx(BBS_Address, 0x1C); // Henter sekunder
    }
    else if(data_flag == 2){
      data_flag += 1;
      batteryBytes[0] = TWDR;
      TWIStartRx(BBS_Address, 0x1D); // Henter minutter
    }
    else if(data_flag == 4){
      data_flag = 0;
      batteryBytes[1] = TWDR;
      i = 1;
    }
  }
  batteryState[0] = ((batteryBytes[0] << 4) | batteryBytes[1]) / 0xFFFF;

  if (batteryState[0] < 20){
    batteryState[1] = 20;
  }
  else if (batteryState[0] < 40){
    batteryState[1] = 40;
  }
  else if (batteryState[0] < 60){
    batteryState[1] = 60;
  }
  else if (batteryState[0] < 80){
    batteryState[1] = 80;
  }
  else{
    batteryState[1] = 100;
  }


  return batteryState;
}


/**
 * @brief Function to turn on and of the led driver using the DAC.
 * @details
 * When DAC is turned on, 0xFFF is written to the DAC to set 5V as output.
 * When DAC is turned off, 0x000 is written ti the DAC to set 0V as output.
 * @param [on_off] Value to turn DAC output on/off.
*/
void setDAC(bool on_off){
  uint8_t first_byte = 0;
  uint8_t second_byte = 0;
  if (on_off == 1){
    first_byte = 0b01001111;
    second_byte = 0b11111111;
    TWIStartTx(DAC_Address, first_byte, second_byte);
  }
  else if (on_off == 0){
    first_byte = 0b01000000;
    second_byte = 0b00000000;
    TWIStartTx(DAC_Address, first_byte, second_byte);
  }
}

/**
 * @brief TWI_vector triggers a statemachien wich runs the TWI communication.
 * @details
 * The TWI is initiated on the outside by TWIStartCon();
 * Before each action is 
*/
ISR(TWI_vect){
  switch (TWI_case){
    // State 1 - Writes the address on the buss.
    case 1:
      TWI_case = 2;
      TWIWrite(address_byte);
      break;
    
    // State 2 - Writes the register to communicate with.
    case 2:
      if (TWI_state == 2){
        TWI_case = 3;
      }
      else {
        TWI_case = 7;
      }
      TWIWrite(register_to_read);
      break;

    // Case 3 - If current communication is rx. Set new start condition.
    case 3:
      TWI_case = 4;
      TWIStartCond();
      break;
    
    // Case 4 - If current comunication is rx. Write adress wit recieve bit set.
    case 4:
      TWI_case = 6;
      TWIWrite(address_byte + 1);
      break;
    
    /*
    case 5:
      TWI_case = 6;
      TWIRecieveWithAck();
      break;
    */

   // Case 6 - Recieve data from slave with Nack.
    case 6:
      TWI_case = 8;
      TWIRecieveWithNack();
      break;

    // Case 7 - If current communication is tx. Write data byte.
    case 7:
      TWI_case = 8;
      TWIWrite(transmit_data);      
      break;
    
    // Case 8 - Set stop condition.
    case 8:
      TWIStopCond();

      // Checks if 
      if(data_flag > 0){
        data_flag += 1;
      }
      

      // Checking queue for tx
      if (TWI_queue[0] == 1){
        address_byte = TWI_queue[1];
        register_to_read = TWI_queue[2];
        transmit_data = TWI_queue[3];

        TWI_state = 1;
        TWI_case = 1;
        TWI_ongoing = true;

        for(uint8_t i = 0; i < 35; i++){
          TWI_queue[i] = TWI_queue[i+4];
        }
        TWIStartCond();
      }

      // Checking queue for rx
      else if(TWI_queue[0] == 2){
        address_byte = TWI_queue[1];
        register_to_read = TWI_queue[2];
        TWI_state = 2;

        TWI_case = 1;

        for(uint8_t i = 0; i < 35; i++){
          TWI_queue[i] = TWI_queue[i+4];
        }
        TWIStartCond();
      }
      // Queue is empty.
      else{
        TWI_case = 0;
        TWI_ongoing = false;
      }
      
      break;

  // Case 0 - If false trig, do nothing.   
  default:
    TWI_ongoing = false;
    break;
  }
}
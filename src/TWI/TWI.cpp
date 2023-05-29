
/*
Kilder brukt for denne koden:
ATmega2560 Datablad: https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/DataSheets/ATmega640-1280-1281-2560-2561-Datasheet-DS40002211A.pdf
https://mansfield-devine.com/speculatrix/2018/02/avr-basics-using-the-i2c-bus-1-clock-speed/
https://github.com/arduino/ArduinoCore-avr/blob/master/libraries/Wire/src/utility/twi.c

RTC DS3231 Datablad: https://www.analog.com/media/en/technical-documentation/data-sheets/DS3231.pdf
DAC MCP4725 Datablad: https://www.farnell.com/datasheets/1470577.pdf
Batterivakt bq27441-G1 Datablad: https://www.ti.com/lit/ds/symlink/bq27441-g1.pdf?HQS=dis-dk-null-digikeymode-dsf-pf-null-wwe&ts=1681129830532&ref_url=https%253A%252F%252Fwww.ti.com%252Fgeneral%252Fdocs%252Fsuppproductinfo.tsp%253FdistId%253D10%2526gotoUrl%253Dhttps%253A%252F%252Fwww.ti.com%252Flit%252Fgpn%252Fbq27441-g1
*/

#include "TWI/TWI.h"

#define f_cpu 16000000 // Definerer cpu klokke frekvensen.

//Addresser for ulike slaver koblet til TWI bussen.
#define RTC_Address 0b11010000 // RTC er satt opp for avlesning.
#define DAC_Address 0b11001100 // Adresse til DAC.
#define BBS_Address 0b10101010 // Batteri vakt.

// Variabler som må settes før TWI kommunikasjon kan initiereres.
volatile uint8_t address_byte;        // Mellomlagrer adressen som skal brukes ved neste overføring.
volatile uint8_t register_to_read;    // Mellomlagrer registert som skal brukes ved neste overføring.
volatile uint8_t transmit_data;       // Mellomlagrer data byte som skal brukes ved neste tx overføring.
volatile uint8_t recieved_data;       // Mellomlagrer mottatt data-byte

volatile uint8_t data_flag = 0;      //Flag som settes når data overføring er fullført.
volatile bool TWI_ongoing = false;   // Forteller om det er en pågående data overføring på gang.
volatile uint8_t TWI_case = 0;       // Inneholder infor om hvilken state som er neste.
volatile uint8_t TWI_state = 0;      // Foterller om det er pågående en tx eller rx operasjon.
volatile uint8_t TWI_queue[39];      // Array som lagrer 40 bytes med data. Dette tilvarer 10 elementer i køen.


/**
 * @brief Function to initiate TWI protocoll on atMEGA2560. 
 * @details 
 * The function sets all registers nEeded to enable the TWI protocoll.
 * The clock frequency on SCL is set to F_SCL = 1 000 000.
 * The ports for SCL and SDA is set up as outputs.
*/
void initTWI(void){
    //Pinne 7 i Registeret PRR0 må settes til 0 for å aktivere TWI.
    PRR0 &= ~(1 << PIN7);
  
    // Setter opp SDA og SCL pinner som utgang.
    DDRD |= (1<<PIN1) | (1<<PIN0);
    PORTD |= (1 << PIN1) | (1 << PIN0);

    // Setter opp RTC - reset pinne som utgang.
    DDRB |= (1 << PIN7);  
    PORTB |= (1<<PIN7);
    
    // Bruker ønsket F_SCL og setter TWBR:
    TWSR &= ~((1<<PIN1)|(1<<PIN0));
    uint8_t TWPS_scales[] = {1, 4, 16, 64};
    uint8_t TWPS_Calculated = TWPS_scales[(TWSR & ((1<<PIN1)|(1<<PIN0)))];
    
    // Beregner instillinger til TWBR og skriver til TWBR.
    TWBR = (uint8_t)(((f_cpu / 100000)-16)/(2*TWPS_Calculated));
    
    // Aktiverer TWI protokollen.
    TWCR |= (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
    sei();
}

/**
 * @brief Function to set the start condition for TWI.
 * @details
 * By setting TWSTA high in the TWCR register the TWI communication is initiated.
*/
void TWIStartCond(void){
  // Setter START Condition ved å skrive til TWCR:
  TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWSTA) | (1 << TWIE));
}

/**
 * @brief Function to set the stop condition for TWI.
 * @details
 * By setting TWSTO high in the TWCR register the TWI communication is ended.
*/
void TWIStopCond(void){
  // Genererer STOP condition:
  TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWSTO) | (1 << TWIE)); 
}

/**
 * @brief Function to send data to the slave.
 * @details
 * By writing the data we want to send in the TWDR register 
 * and setting TWINT high in TWCR a byte is sent on the TWI bus.
 * @param data A data byte to send to the slave.
*/
void TWIWrite(uint8_t data){
  // Skriver byte inn i TWDR registere.
  TWDR = data;
  // Sender innholdet i TWDR ut på TWI bussen.
  TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWIE));
}

/**
 * @brief Function to recieve data and send acknowledge.
 * @details
 * When data is recieved in the TWDR register and send acknowledge bit.
 * Used when it is expected to recieve more data before endig transmition.
 * @return Returns the recieved byte in TWDR.
*/
uint8_t TWIRecieveWithAck(void){
  // Tar imot data og svarer med ack flagget satt.
  TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWEA) | (1 << TWIE));
  return TWDR;
}

/**
 * @brief Function to recieve data without sending acknowledge.
 * @details
 * When data is recieved in the TWDR register.
 * Wen recieving the last expected byte answer with no acknowledge.
 * @return Returns the recieved byte in TWDR.
*/
uint8_t TWIRecieveWithNack(void){
  // Mottar data uten å ha ack flagget satt.
  TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWIE));
  return TWDR;
}

uint8_t getStatusCode(void){
  uint8_t StatusTWI = (TWSR & ~(0x07));

  return StatusTWI;
}



/**
 * @brief Function to start TWI data transmition. 
 * @details 
 * The function checks if there is already an ogoing TWI operation.
 * If this is the case the transmitiondata is stored int the queue.
 * If the TWI buss is free the statemachine is triggered wich will run independently by interrupts.
 * @param address The TWI address for the module to communicate with.
 * @param write_reg The register to write data to on the slave.
 * @param write_data Tha data we want to send over to the slave.
*/
void TWIStartTx(uint8_t address, uint8_t write_reg, uint8_t write_data){
  // Sjekker om det er en pågående TWI kommunikasjon på gang.
  if (TWI_ongoing == false){
    // Om TWI ikke er aktiv skrives de nødvendige dataene inn i de globale variblene som benyttes underveis i kommunikasjonen.
    address_byte = address;
    register_to_read = write_reg;
    transmit_data = write_data;

    // Variabler som starter opp og styrer TWI kommunikasjonen.
    TWI_state = 1;
    TWI_case = 1;
    TWI_ongoing = true;
    TWIStartCond();
    
  }
  else if (TWI_ongoing == true){
    // Om det er en pågående TWI overføring blir variablene som brukes i kommunikasjonen mellom lagret i en kø.
    for(uint8_t i = 0; i < 36; i += 4){
      //Sjekker hvert 4 element køen til den finner ledig plass.
      if (TWI_queue[i] == 0){
        TWI_queue[i] = 1;
        TWI_queue[i+1] = address;
        TWI_queue[i+2] = write_reg;
        TWI_queue[i+3] = write_data;
      }
    }
  }
}


/**
 * @brief Function to start TWI datatransfer request. 
 * @details 
 * The function checks if there is already an ogoing TWI operation.
 * If this is the case the transmitiondata is stored int the queue.
 * If the TWI buss is free the a statemachine is triggered wich will run independently by interrupts.
 * @param address The TWI adress for the module to communicate with.
 * @param write_reg The register to write data to on the slave.
*/
void TWIStartRx(uint8_t address, uint8_t read_register){
  // Sjekker om det er en pågående TWI kommunikasjon på gang.
  if (TWI_ongoing == false){
    // Om TWI ikke er aktiv skrives de nødvendige dataene inn i de globale variblene som benyttes underveis i kommunikasjonen.
    address_byte = address;
    register_to_read = read_register;

    // Variabler som starter opp og styrer TWI kommunikasjonen.
    TWI_state = 2;
    TWI_case = 1;
    TWI_ongoing = true;
    TWIStartCond();
  }
  else if (TWI_ongoing == true){
    // Om det er en pågående TWI overføring blir variablene som brukes i kommunikasjonen mellom lagret i en kø.
    for(uint8_t i = 0; i < 36; i += 4){
      //Sjekker hvert 4 element køen til den finner ledig plass.
      if (TWI_queue[i] == 0){
        TWI_queue[i] = 2;
        TWI_queue[i+1] = address;
        TWI_queue[i+2] = read_register;
      }
    }
  }
}


/**
 * @brief Function recieve raw Date and convert to decimal.
 * @details
 * First the registers 0x04, 0x05, 0x06 is read from and saved in the array rawDate.
 * Then the rawDate is converted to the date in decimal and saved in the global array calckDate.
 * If an error occurs in the communication the function will return [0,0,0] and error code 12 will be set.
 * The result will be saved in the gloval array calcDate.
*/
void getDate(void){
  uint8_t rawDate[3];

  bool i = true;  
  // While løkke som kjører frem til alle dataene er mottatt.
  while(i){  
    
    // data-flag inkrementeres hver gan ny transmisjon er starter og hver gang en er avsluttet.
    // Hver gang data_flag er ett partall vil det være mottat data og rawDate oppdateres med motatt byte.
    // Når alle dataene er motatt vil i settes lav og koden går videre til prosessering av data.
    if (data_flag == 0){
      // Oppstart av TWI kommunikasjonen.
      rawDate[0] = 0; 
      rawDate[1] = 0;
      rawDate[2] = 0;
      data_flag = 1;

      // Hentig av rådata for dato startes
      TWIStartRx(RTC_Address, 0x04); 
    }
    else if(data_flag == 2){
      // Rådata for dato er mottat
      data_flag = 3;
      rawDate[0] = recieved_data;
      // Henting av rådata for måned startes
      TWIStartRx(RTC_Address, 0x05); 
    }
    else if(data_flag == 4){
      // Rådata for måned er motatt
      data_flag = 5; 
      rawDate[1] = recieved_data;
      // Henting av rådata for år startes
      TWIStartRx(RTC_Address, 0x06);
    }
    else if(data_flag == 6){ 
      // Rådata for år er mottatt
      rawDate[2] = recieved_data;
      data_flag = 0;
      // Kommunikasjon avsluttes.
      i = false;
    }

    // Sjekker om det er dukket opp noen brudd i kommunikasjonen.
    // Avbryter kommunikasjonen og returnerer [0,0,0]
    if (getStatusCode() == 0x38){
      TWIStopCond();
      rawDate[0] = 0;
      rawDate[1] = 0;
      rawDate[2] = 0;
      get_error[12] = 1;
      data_flag = 0;
      i = false;
    }
    else{
      get_error[12] = 0;
    }
  }

  // Formaterer tallene riktig med bit shifting, ganging og addering.
  calcDate[0] = ((rawDate[0] >> 4) & 0x0F)*10 + (rawDate[0] & 0x0F);  // Beregner dato
  calcDate[1] = ((rawDate[1] >> 4) & 0x0F)*10 + (rawDate[1] & 0x0F);  // Beregner måned
  calcDate[2] = ((rawDate[2] >> 4) & 0x0F)*10 + (rawDate[2] & 0x0F);  // Beregner år
}

/**
 * @brief Function to change integer values for date to one string.
 * @param dateArray The functions uses the Array output from getDate.
 * @return One stirng in dd-mm-yy format.
*/
char *formatDateToChar(uint8_t dateArray[3]){
  dateChar[0] = '\0';

  char dd[2];
  char mm[2];
  char yy[2];

  sprintf(dd, "%d", dateArray[0]);
  sprintf(mm, "%d", dateArray[1]);
  sprintf(yy, "%d", dateArray[2]);

  strcat(dateChar, dd);
  strcat(dateChar, "-");
  strcat(dateChar, mm);
  strcat(dateChar, "-");
  strcat(dateChar, yy);

  return dateChar;
}

/**
 * @brief Function recieve raw time and convert to decimal.
 * @details
 * First the registers 0x00, 0x01, 0x02 is read from and saved in the array rawTime.
 * Then the rawTime is converted to the time in decimal and saved in the global array calcTime.
 *  If an error occurs in the communication the function will returrn [0,0,0] and error code 13 will be set.
 * The result will be saved in the gloval array calcTime.
*/
void getTimeStamp(void){
  uint8_t rawTime[3];

  bool i = true;  
  // While løkke som kjører frem til alle dataene er mottatt.
  while(i){  
    // data-flag inkrementeres hver gan ny transmisjon er starter og hver gang en er avsluttet.
    // Hver gang data_flag er ett partall vil det være mottat data og rawDate oppdateres med motatt byte.
    // Når alle dataene er motatt vil i settes lav og koden går videre til prosessering av data.
    
    if (data_flag == 0){
      // Oppstart av TWI kommunikasjonen.
      rawTime[0] = 0; 
      rawTime[1] = 0;
      rawTime[2] = 0;
      data_flag = 1;
      // Henting av rådata for sekunder startes
      TWIStartRx(RTC_Address, 0x00);
    }
    else if(data_flag == 2){
      // Rådata for sekunder er motatt.
      data_flag += 1;
      rawTime[0] = recieved_data;
      // Henting av rådata for minutter startes
      TWIStartRx(RTC_Address, 0x01);
    }
    else if(data_flag == 4){
      // Rådata for minutter er motatt.
      data_flag += 1;
      rawTime[1] = recieved_data;
      // Henting av rådata for timer startes
      TWIStartRx(RTC_Address, 0x02);
    }
    else if(data_flag == 6){ 
      // Rådata for timer er motatt.
      rawTime[2] = recieved_data;
      data_flag = 0;
      // Kommunikasjon avsuttes.
      i = false;
    } 

    // Sjekker om det er dukket opp noen brudd i kommunikasjonen.
    // Avbryter kommunikasjonen og returnerer [0,0,0]
    if (getStatusCode() == 0x38){
      TWIStopCond();
      rawTime[0] = 0;
      rawTime[1] = 0;
      rawTime[2] = 0;
      get_error[13] = 1;
      data_flag = 0;
      i = false;
    }
    else{
      get_error[13] = 0;
    }
  }
  // Formaterer tallene riktig med bit shifting, ganging og addering.
  calcTime[0] = ((rawTime[0] >> 4) & 0x07)*10 + (rawTime[0] & 0x0F);  // Beregner sekunder
  calcTime[1] = ((rawTime[1] >> 4) & 0x07)*10 + (rawTime[1] & 0x0F);  // Beregner minutter
  calcTime[2] = ((rawTime[2] >> 4) & 0x03)*10 + (rawTime[2] & 0x0F);  // Beregner timer
}

/**
 * @brief Function to change integer values for time to one string.
 * @param timeArray The functions uses the Array output from getTimeStamp.
 * @return One sting in hh:mm:ss format.
*/
char *formatTimeToChar(uint8_t timeArray[3]){
  timeChar[0] = '\0';

  char seconds[2];
  char minutes[2];
  char hours[2];

  sprintf(seconds, "%d", timeArray[0]);
  sprintf(minutes, "%d", timeArray[1]);
  sprintf(hours, "%d", timeArray[2]);

  strcat (timeChar, hours);
  strcat (timeChar, ":");
  strcat (timeChar, minutes);
  strcat (timeChar, ":");
  strcat (timeChar, seconds);

  return timeChar;
}


/**
 * @brief Function to change integer values for date to one string.
 * @param dateArray The functions uses the Array output from getDate.
 * @return One sting in dd-mm-yy format.
*/
char *formatDateTimeToChar(uint8_t dateArray[3], uint8_t timeArray[3]){
  dateTimeChar[0] = '\0';
  char dd[2];
  char mm[2];
  char yy[2];

  sprintf(dd, "%d", dateArray[0]);
  sprintf(mm, "%d", dateArray[1]);
  sprintf(yy, "%d", dateArray[2]);

  strcat(dateTimeChar, dd);
  strcat(dateTimeChar, "-");
  strcat(dateTimeChar, mm);
  strcat(dateTimeChar, "-");
  strcat(dateTimeChar, yy);

  strcat(dateTimeChar, " ");

  char seconds[2];
  char minutes[2];
  char hours[2];

  sprintf(seconds, "%d", timeArray[0]);
  sprintf(minutes, "%d", timeArray[1]);
  sprintf(hours, "%d", timeArray[2]);

  strcat (dateTimeChar, hours);
  strcat (dateTimeChar, ":");
  strcat (dateTimeChar, minutes);
  strcat (dateTimeChar, ":");
  strcat (dateTimeChar, seconds);

  return dateTimeChar;
}

/**
 * @brief Function to reset the RTC by updating the time and date.
 * @details
 * The funcion converts the decimal inputs to binary coded decimal format.
 * Then each value is written to the respective register on the RTC.
 * @param sec Sets the seconds [0-59]
 * @param min Sets the minutes [0-59]
 * @param hour Sets the hours [0-23]
 * @param date Sets the date [0-31]
 * @param month Sets the month [0-12]
 * @param year Sets the year [0-99]
*/
void resetRTC(uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year){

  // Omformaterer de ulike tallene tilpasset formater som skal inn i RTC-en.
  uint8_t calcSec = ((sec / 10) << 4) | (sec % 10);
  uint8_t calcMin = ((min / 10) << 4) | (min % 10);
  uint8_t calcHour = ((hour / 10) << 4) | (hour % 10);
  
  uint8_t calcDate = ((date / 10) << 4) | (date % 10);
  uint8_t calcMonth = ((month / 10) << 4) | (month % 10);
  uint8_t calcYear = ((year / 10) << 4) | (year % 10);
  
  bool i = true;
  // While løkke som kjører frem til alle dataene er mottatt.
  while (i){
    // data-flag inkrementeres hver gan ny transmisjon er starter og hver gang en er avsluttet.
    // Hver gang data_flag er ett partall vil det være mottat data og rawDate oppdateres med motatt byte.
    // Nåar alle dataene er motatt vil i settes lav og koden går videre til prosessering av data.
    if (data_flag == 0){ 
      data_flag = 1;
      // Skriver oppdatert sekunder til RTC-en.
      TWIStartTx(RTC_Address, 0x00, calcSec);
    }
    else if (data_flag == 2){
      data_flag = 3;
      // Skriver oppdatert minutter til RTC-en.
      TWIStartTx(RTC_Address, 0x01, calcMin);
    }
    else if (data_flag == 4){
      data_flag = 5;
      // Skriver oppdatert timer til RTC-en.
      TWIStartTx(RTC_Address, 0x02, calcHour);
    }
    else if (data_flag == 6){
      data_flag = 7;
      // Skriver oppdatert dato til RTC-en.
      TWIStartTx(RTC_Address, 0x04, calcDate);
    }
    else if (data_flag == 8){
      data_flag = 9;
      // Skriver oppdatert måned til RTC-en.
      TWIStartTx(RTC_Address, 0x05, calcMonth);
    }
    else if (data_flag == 10){
      data_flag = 11;
      // Skriver oppdatert år til RTC-en.
      TWIStartTx(RTC_Address, 0x06, calcYear);
      // Avslutter while-loop
      i = false;
    }
  }
}


/**
 * @brief Retrieve the current battery state
 * @details
 * Reads from the registers 0x1C and 0x1D to get the battery % value in the interval [0-100].
 * Calculate values for battery indicator on screen [0-5]
 * Also reads the battery state of health.
 * If an error occurs in the communication the function will returrn [0,0,0] and error code 15 will be set.
 * If the battery state of health is below 30% error code 16 will be set.
 * If the battery % is below 20% error code 1 will be set.
 * All parameters is saved in global array batteryState.
*/
void getBatteryState(void){
  data_flag = 0;
  uint8_t batteryBytes[4];

  bool i = true;  
  // While løkke som kjører frem til alle dataene er mottatt.
  while(i){  
    // data-flag inkrementeres hver gan ny transmisjon er starter og hver gang en er avsluttet.
    // Hver gang data_flag er ett partall vil det være mottat data og rawDate oppdateres med motatt byte.
    // Når alle dataene er motatt vil i settes lav og koden går videre til prosessering av data.
    
    if (data_flag == 0){
      //Starter TWI kommunikasjon
      data_flag += 1;
      // Henter første byte for batteriprosent.
      TWIStartRx(BBS_Address, 0x1C);
    }
    else if(data_flag == 2){
      // Første byte er mottatt
      data_flag += 1;
      batteryBytes[0] = recieved_data;
      // Henter andre byte for batteriprosent.
      TWIStartRx(BBS_Address, 0x1D);
    }
    else if(data_flag == 4){
      // Andre byte er mottatt
      data_flag += 1;
      batteryBytes[1] = recieved_data;
      // Henter første byte for StateOfHealth prosent.
      TWIStartRx(BBS_Address,0x20);
    }
    else if(data_flag == 6){
      // Tredje byte er mottatt
      data_flag += 1;
      batteryBytes[2] = recieved_data;
      // Henter andre byte for StateOfHealth prosent.
      TWIStartRx(BBS_Address,0x21);
    }
    else if(data_flag == 8){
      // Fjerde byte er mottatt
      data_flag = 0;
      batteryBytes[3] = recieved_data;
      i = false;
    }

    // Sjekker om det er dukket opp noen brudd i kommunikasjonen.
    // Avbryter kommunikasjonen og returnerer [0,0,0]
    if (getStatusCode() == 0x38){
      TWIStopCond();
      batteryBytes[0] = 0;
      batteryBytes[1] = 0;
      batteryBytes[2] = 0;
      get_error[15] = 1;
      data_flag = 0;
      i = false;
    }
    else{
      get_error[15] = 0;
    }
  }
  // Finne batteri prosent - Setter sammen verdiene hentet for % entet fra registerene 0x1C og 0x1D
  batteryState[0] = ((batteryBytes[0] << 4) | batteryBytes[1]) / 0xFFFF;

  // Finner StateOfHealth prosent - Setter sammen verdiene hentet for % entet fra registerene 0x20 og ox21
  batteryState[2] = ((batteryBytes[2] << 4) | batteryBytes[3]) / 0xFFFF;
  // Setter error om helsen begynner å bli dårlig.
  if (batteryState[2] < 30){
    get_error[16] = 1;  // Oppdaterer feilmelding til batteriets helse.
  }
  else{
    get_error[16] = 0;  // Oppdaterer feilmelding til batteriets helse.
  }

  // Finner verdi som skal vises på batteri ikonet på skjermen i femttedeler.
  if (batteryState[0] < 20){
    get_error[1] = 1;  // Oppdaterer feilmelding til batteri %.
    batteryState[1] = 20;
  }
  else if (batteryState[0] < 40){
    get_error[1] = 0;  // Oppdaterer feilmelding til batteri %.
    batteryState[1] = 40;
  }
  else if (batteryState[0] < 60){
    get_error[1] = 0;  // Oppdaterer feilmelding til batteri %.
    batteryState[1] = 60;
  }
  else if (batteryState[0] < 80){
    get_error[1] = 0;  // Oppdaterer feilmelding til batteri %.
    batteryState[1] = 80;
  }
  else{
    get_error[1] = 0;  // Oppdaterer feilmelding til batteri %.
    batteryState[1] = 100;
  }
}


/**
 * @brief Function to turn on and of the led driver using the DAC.
 * @details
 * When DAC is turned on, 0xFFF is written to the DAC to set 5V as output.
 * When DAC is turned off, 0x000 is written ti the DAC to set 0V as output.
 * If an error occurs in the communication the critical error code 14 will be set.
 * @param on_off Value to turn DAC output on/off.
*/
void setDAC(bool on_off){
  // Lagring av rette verdier som skal sendes til DAC.
  uint8_t first_byte = 0;
  uint8_t second_byte = 0;

  if (on_off == 1){
    // Når DAC skrus på skal dette sendes for å sette 5V på utgangen.
    first_byte = 0b01001111;
    second_byte = 0b11111111;
    TWIStartTx(DAC_Address, first_byte, second_byte);
  }
  else if (on_off == 0){
    // Når DAC skrus av skal dette sendes for å sette oV på utgangen.
    first_byte = 0b01000000;
    second_byte = 0b00000000;
    TWIStartTx(DAC_Address, first_byte, second_byte);
  }
  // Sjekker om det er dukket opp noen brudd i kommunikasjonen.
  // Avbryter kommunikasjonen
  while (TWI_ongoing == true){
    if (getStatusCode() == 0x38){
      TWIStopCond();
      get_error[14] = 1;
    }
    else{
      get_error[14] = 0;
    }
  }
}

/**
 * TWI_vector triggers a statemachien wich runs the TWI communication.
 * The TWI is initiated on the outside by TWIStartCon();
 * It also applys logic for the queue at the end.
*/
ISR(TWI_vect){
  switch (TWI_case){
    // State 1 - Skriver slave adressen på TWI bussen.
    case 1:
      TWI_case = 2;
      TWIWrite(address_byte);
      break;
    
    // State 2 - Skriver registeret som skal kommuniseres med på TWI bussen.
    case 2:
      if (TWI_state == 2){
        TWI_case = 3; // Neste state starter RX modus.
      }
      else {
        TWI_case = 6; // Neste state fortsetter TX modus.
      }
      TWIWrite(register_to_read);
      break;

    // Case 3 - Om pågående kommunikasjoen er RX. Sett ny start betingelse.
    case 3:
      TWI_case = 4;
      TWIStartCond();
      break;
    
    // Case 4 - Om pågående kommunikasjoen er RX. Send adresse på nytt med RX bit satt.
    case 4:
      TWI_case = 6;
      TWIWrite(address_byte + 1);
      break;
    
   // Case 5 - Om pågående kommunikasjoen er RX. Motta data uten å sette Acknowledge.
    case 5:
      TWIRecieveWithNack();
      if (getStatusCode() == 0x58){
        recieved_data = TWDR;
        TWI_case = 7;
      }
      break;

    // Case 6 - Om pågående kommunikasjoen er TX. Skriv data til slave.
    case 6:
      TWI_case = 8;
      TWIWrite(transmit_data);      
      break;
    
    // Case 7 - Setter stopp betingelse.
    case 7:
      TWIStopCond();

      // Dataflagg brukes i funksjonene som henter flere mengder data om gangen. 
      // Når data_flag er trigget skal den inkrementeres hver gang data er motatt.
      if(data_flag > 0){
        data_flag += 1;
      }
      
      // Om data_flag ikke er aktivert sjekkes køen for om det er andre dataOverføringer som står på vent.
      else if (TWI_queue[0] == 1){
        // Om første element i køen er 1 skal det startes en tx operasjon.
        // De globale variblene som benyttes underveis i kommunikasjonen settes.
        address_byte = TWI_queue[1];
        register_to_read = TWI_queue[2];
        transmit_data = TWI_queue[3];

        // Variabler som starter opp og styrer TWI kommunikasjonen.
        TWI_state = 1;
        TWI_case = 1;
        TWI_ongoing = true;

        // Og arrayet TWI_queue shiftes 4 fremover.
        for(uint8_t i = 0; i < 35; i++){
          TWI_queue[i] = TWI_queue[i+4];
        }
        // Ny TWI kommunikasjon startes.
        TWIStartCond();
      }

      // Checking queue for rx
      else if(TWI_queue[0] == 2){
        // Om første element i køen er 1 skal det startes en tx operasjon.
        // De globale variblene som benyttes underveis i kommunikasjonen settes.
        address_byte = TWI_queue[1];
        register_to_read = TWI_queue[2];

        // Variabler som starter opp og styrer TWI kommunikasjonen.
        TWI_state = 2;
        TWI_case = 1;
        TWI_ongoing = true;

        // Køen shiftes 4 fremover.
        for(uint8_t i = 0; i < 35; i++){
          TWI_queue[i] = TWI_queue[i+4];
        }

        // Ny TWI kommunikasjon startes.
        TWIStartCond();
      }
      // Om køen er tom avsluttes hele kommunikasjonen.
      else{
        TWI_case = 0;
        TWI_ongoing = false;
      }
      
      break;

  // Case 0 - IDLE indikere feil trigging - gjør ingenting.   
  default:
    TWI_ongoing = false;
    break;
  }
}
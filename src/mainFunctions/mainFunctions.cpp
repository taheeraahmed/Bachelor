#include <mainFunctions/mainFunctions.h>

void initiateSystem(void){
    initADC();
    initGetTime();
    initLedPins();
    initPort();
    initTimer0();
    initTimer3();
    initTWI();

    sei();
}

void runMenu(void){
    //Her kjøres Mina sin meny kode.
}

void testDataUpdate(unsigned long testLength){
    // Timer variables:
    unsigned long test_time_start = getTime();
    unsigned long test_time_new = getTime();
    unsigned long test_time_old;

    uint16_t ms_to_sample = 60000; // Setter tid mellom hver sample til 60 000 ms = 1 minutt.

    // Initializes .csv file:
    /*
    char temp_headers[50] = "datetime,temp_pcb,temp_air,temp_skin,temp_led";
    char error_headers[50] = "datetime,error_code,error_msg";
    uint8_t patient_id = 123;
    uint8_t start_time = 0;
    */
    // Turns NIR light on
    //setNIR()   -> Finn ut hva som skal være parameterene.
    testIndicatorOn();    
    greenLedBlink();
    while ((test_time_new - test_time_start) <= (testLength*1000)){
        
        test_time_new = getTime();
        // Every minute the program samples data and writes to the csv file.
        if (test_time_new - test_time_old > ms_to_sample){
            /*
            formatDateTimeToChar(getDate(), getTimeStamp());

            //set fklagg adc + temp value array (0: Led , 1: pcb, 2: skin, 3:air)
            char *data = convertDataToChar(1, 2, 3, 4, dateTimeChar);
	          writeToFile(file_temp, data);
            */
            test_time_old = test_time_new;
        }

        /*
        if (write_error[0] != 0){
            redLedBlink();
            skriv til error fil.   
        }
        else{
            redLedOff();
        }
        */
    }
    endNIR();
    testIndicatorOff();
    greenLedOff();
}
void setSystemSleep(void){
    //clearScreen();
    SMCR = (1 << PIN2) | (1 << PIN0);
}
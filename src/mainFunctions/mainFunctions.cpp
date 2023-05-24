#include "mainFunctions/mainFunctions.h"


uint8_t system_state = 0;

// Initierer globale variabler som brukes i videre kode.
/*
uint8_t calcDate[3];
uint8_t calcTime[3];
uint8_t batteryState[3];
*/

char timeChar[8];
char dateChar[8];
char dateTimeChar[17];

volatile bool greenButtonTrigg = false;
char minutes_char[2];
char seconds_char[2];

bool critical_error_detect = false;

// Initialisering av .csv filer.
    char temp_headers[50] = "datetime,temp_pcb,temp_air,temp_skin,temp_led";
    char error_headers[50] = "datetime,error_code,error_msg";
    char info_header[29] = "Information about experiment";

/**
 * @brief En funksjon for å initiere systemet.
 * @details Denne funksjonen kaller på alle initieringsfunksjonene i systemet.
 */
void initiateSystem(void){
    
    initADC();
    initGetTime();
    initLedPins();
    initPort();
    initTimer2();
    initTimer3();
    initTWI();
    initScreen();
    initPinChangeInterrupt();

    Sd2Card card;
    MEMORY_EXTENSION_PINS mem_ext_pins;
    initSD(mem_ext_pins.CS);
    initCard(mem_ext_pins.CS, card);

    system_state = 1;

    sei();  // Aktiverer interrupts.
}

/**
 * @brief En funksjon kjører systemet under førsøket.
 * @details Denne funksjonen kjører initierer førsøket ved å åpnet alle filer.
 * Deretter går den inn i en hvile loop som kjører til testtiden er nådd eller testen avbrytes.
 * Hver minutt innhentes verdier fra temperatursensorene og oppdaterer .csv filen.
 * Om det oppstår feilmeldinger underveis vil disse skrives til en egen .csv fil.
 * @param testLength Lengden på testen i minutter.
 */
void testDataUpdate(unsigned long testLength){
    // Oppsett av variabler knyttet til tidtaking av forsøket.
    unsigned long test_time_start = getTime();
    unsigned long test_time_new = getTime();
    unsigned long test_time_old;
    unsigned long testLength_ms = testLength*60000;

    unsigned long ms_to_sample = 60000; // Setter tid mellom hver sample til 60 000 ms = 1 minutt.
     runExperimentScreen(batteryState[1], dateChar, getRemainingSeconds(test_time_new, testLength), getRemainingMinutes(test_time_new, (testLength)), threshold_skin_contact);

    TestChoices test;    
    test.experiment_id = getExperimentId();

    // Lager filmappe og finavn.
    createDirectory(test.experiment_id);
    char *file_temp = createFileName(TEMP, test);
    char *file_error = createFileName(ERROR, test);
    char *file_info = createFileName(INFO, test);
    
    // Lager filer basert på filnavnene.
    createFile(temp_headers, file_temp, test);
    createFile(error_headers, file_error, test);
    createFile(info_header, file_info, test);
    writeInfoFile(test, formatDateTimeToChar(calcDate, calcTime), file_info);

    // Skrur på NIR-lys med innstillingene satt i forskerMeny.
    calcLedID();
    
    startNIR(test.mode, test.pvm_freq, ID_NIR_LED); // NIRmode, NIRfreq, R_ID

    // Skrur på LED-indikatorer for at forsøket er i gang.
    testIndicatorOn();    
    greenLedBlink();

   

    // Hovedløkke for forsøket.
    while ((test_time_new - test_time_start) < (testLength_ms)){
        
        // Temperatursensorene oppdateres.
        setFlaggADC();
        test_time_new = getTime();

        // Hvert minutt oppdateres .csv filen med nye temperaturverdier.
        if (test_time_new - test_time_old > ms_to_sample){
            // Henter dato og tid for tidsstempel;
            //getDate();
            //getTimeStamp();
            formatDateToChar(calcDate);
            formatDateTimeToChar(calcDate, calcTime);

            // Oppdaterer batteriStatus
            //getBatteryState();

            // Skjerm oppdateres:
            runExperimentScreen(3, "blabla", "22", "33", 1);
            //Skriver data til .csv fil (0: Led , 1: pcb, 2: skin, 3:air, 4: datetime)
            char *data = convertDataToChar(temp_value_array[0], temp_value_array[1], temp_value_array[2], temp_value_array[3], dateTimeChar);
            writeToFile(file_temp, data);
            
            test_time_old = test_time_new;
        }
        /*
        // Sjekker om det er dukket opp noen feilmeldinger
        if (write_error[0] == 1){
            redLedBlink();
            // Henter dato og tid for tidsstempel;
            //getDate();
            //getTimeStamp();
            formatDateTimeToChar(calcDate, calcTime);

            uint8_t i = 0;
            // Sjekker hvert element i feimeldingslisten til den er tom.
            while (write_error[i] != 0){
                
                // Formaterrer feilmelding til char "0x--"
                char errorID[] = "00";
                errorID[0] = write_error[i]/10;
                errorID[1] = write_error[i]%10;

                // Skriver feilmelding til fil.
                char *error = convertErrorToChar(1, errorID, formatDateTimeToChar(calcDate, calcTime));
                writeToFile(file_error, error);
                // Resetter error melding når den er skrevet.
                write_error[i] = 0;
                i += 1;

                if ((write_error[i] != 1) & (write_error[i] != 12) & (write_error[i] != 13) & (write_error[i] != 15) & (write_error[i] != 16)){
                    criticalErrorScreen();
                    critical_error_detect = true;
                }

                
                //Om hudkontakt blir mistet venter systemet i ett minutt før forsøket avsluttet.
                
                if (threshold_skin_contact == 1){
                    unsigned long skin_error_start = getTime();
                    unsigned long skin_error_curent;
                    uint16_t skin_error_exit_time = 60000;

                    noSkinContactScreen();
                    
                    
                    while (((skin_error_start - skin_error_curent) < skin_error_exit_time) && (threshold_skin_contact == 1)){
                        // Skriver feilmelding til fil.
                        get_error[21] = 1;
                        char *error = convertErrorToChar(1, "21", formatDateTimeToChar(calcDate, calcTime));
                        writeToFile(file_error, error);
            
                        skin_error_curent = getTime();
                        }
                    }
                    // Når ett minutt er gått sjekkes hudkontakt på nytt for å bestemme om forsøket skal avbrytes eller fortsettes.
                    if (threshold_skin_contact == 1){
                        break;
                    }
                    else{
                     get_error[21] = 0;   
                    }     
                    
            }
        }
        else{
            redLedOff();
        }
        */
        
    }
    // Forsøk avsluttes - NIR-lys skrus av og indikatorer deaktiveres.
    void endNIR(void);
    testIndicatorOff();
    greenLedOff();
}

/**
 * @brief En funksjon for å sette systemet i dvale.
 * @details Denne funksjonen setter systemet i dvale ved å sette sleep mode til Power-down.
 */
void setSystemSleep(void){
    SMCR = (1 << PIN2) | (1 << PIN0);
}

/**
 * @brief Henter ut gjenværende hele minutter av forsøket
 * 
 * @param start Starttiden for forsøket
 * @param duration Lengden på forsøket i minutter
 * @return uint8_t Antall gjenværende minutter av forsøket
 */
char *getRemainingMinutes(unsigned long start, unsigned long duration){
    unsigned long current_time = getTime();
    unsigned long remaining_time_ms = (duration*60000) - (current_time - start);

    uint8_t remaining_seconds = remaining_time_ms/1000;
    uint8_t remaining_minutes = remaining_seconds/60;

    sprintf(minutes_char, "%d", remaining_minutes);

    if (remaining_minutes <= 3){
        greenLedBlink();
    }
    return minutes_char;
}

/**
 * @brief Henter ut gjenværende sekunder av forsøket når antall minutter er fratrukket
 * 
 * @param start Starttiden for forsøket
 * @param duration Lenget på forsøket i minutter
 * @return uint8_t Antall gjenværende sekunder av forsøket fratrukket minutter
 */
char *getRemainingSeconds(unsigned long start, unsigned long duration){
    unsigned long current_time = getTime();
    unsigned long remaining_ms = (duration*60000) - (current_time - start);
    uint8_t remaining_seconds = remaining_ms/1000;
    uint8_t remaining_seconds_removed_minutes = remaining_seconds%60;

    sprintf(seconds_char, "%d", remaining_seconds_removed_minutes);
    return seconds_char;
}

/**
 * @brief Funksjon som styrer systemflyt
 * @details Denne funksjoenen opererer som en tilstandsmaskin som kontrollerer hvordan systemet opererer til enhver tid.
 * Store deler av flyten knyttes direkte til skjermfunksjonene i "menu.h"
 */
void runSystem(void){
  setFlaggADC();

  switch (system_state){
    case 0:
        // Systemet sover. Ingentig skjer.
        // Neste tilstand trigges av avbrudd levert fra grønn knapp.
        break;
    case 1:
        // System is initiated
        initiateSystem();
        // APT logo is shown
        // Videre styres systemet av menyen
        systemWaiting();
        system_state = 2;
        
        break;

    case 2:
        // Skrur av skjerm og setter systemet i dvale.
        clearScreen();
        setSystemSleep();
        system_state = 0;
        break;
        
  }
}

/**
 * @brief Aktiverer avbrudd på den grønne knappen.
 */
void initPinChangeInterrupt(void){
  // Setting  
  DDRJ &= ~(1 << PIN1);
  
  // set up interrupt vector table
  PCICR |= (1 << PIN1); // Enable PCINT for Port J
  PCMSK1 |= (1 << PIN1); // Enable PCINT3 for PORTJ PIN!
}

ISR(PCINT1_vect){
    // Når systemet sover vil trykk på grønn knapp vekke systemet og gå til skjermens forside.    
    if ((system_state == 0)){
        SMCR &= ~((1 << PIN2) | (1 << PIN0));
        system_state = 1;
    }
    
    if ((system_state == 1) && (threshold_skin_contact == 1)){
        // Start forsøk i meny.
        greenButtonTrigg = true;
    }
    else{
        greenButtonTrigg = true;
    }
    
}
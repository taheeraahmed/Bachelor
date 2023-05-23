#include "mainFunctions/mainFunctions.h"


// Initierer globale variabler som brukes i videre kode.
uint8_t calcDate[3];
uint8_t calcTime[3];
uint8_t batteryState[3];

char timeChar[8];
char dateChar[8];
char dateTimeChar[17];

int write_error[4];

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

    Sd2Card card;
    MEMORY_EXTENSION_PINS mem_ext_pins;
    initSD(mem_ext_pins.CS);
    initCard(mem_ext_pins.CS, card);

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

    uint16_t ms_to_sample = 60000; // Setter tid mellom hver sample til 60 000 ms = 1 minutt.

    // Henter dato og tid for tidsstempel
    getDate();
    getTimeStamp();

    // Initialisering av .csv filer.
    char temp_headers[50] = "datetime,temp_pcb,temp_air,temp_skin,temp_led";
    char error_headers[50] = "datetime,error_code,error_msg";
    char info_header[29] = "Information about experiment";
    
    // Initialisering av testvalg.
    TestChoices test;
    test.mode = PLACEBO;
    test.duration = DURATION_30_MIN;
    test.pvm_freq = LOW_FREQUENCY;
    test.patient_id = 123;
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
    startNIR(0,0,0); // NIRmode, NIRfreq, R_ID

    // Skrur på LED-indikatorer for at forsøket er i gang.
    testIndicatorOn();    
    greenLedBlink();

    // Hovedløkke for forsøket.
    while ((test_time_new - test_time_start) <= (testLength*1000)){
        // Temperatursensorene oppdateres.
        setFlaggADC();
        test_time_new = getTime();

        // Hvert minutt oppdateres .csv filen med nye temperaturverdier.
        if (test_time_new - test_time_old > ms_to_sample){
            // Henter dato og tid for tidsstempel;
            getDate();
            getTimeStamp();
            formatDateTimeToChar(calcDate, calcTime);

            //Skriver data til .csv fil (0: Led , 1: pcb, 2: skin, 3:air, 4: datetime)
            char *data = convertDataToChar(temp_value_array[0], temp_value_array[1], temp_value_array[2], temp_value_array[3], dateTimeChar);
            writeToFile(file_temp, data);
            
            test_time_old = test_time_new;
        }

        // Sjekker om det er dukket opp noen feilmeldinger
        if (write_error[0] == 1){
            redLedBlink();
            // Henter dato og tid for tidsstempel;
            getDate();
            getTimeStamp();
            formatDateTimeToChar(calcDate, calcTime);

            uint8_t i = 0;
            // Sjekker hvert element i feimeldingslisten til den er tom.
            while (write_error[i] != 0){
                
                // Formaterrer feilmelding til char "0x--"
                char errorID[] = "0x00";
                errorID[2] = write_error[i]/16;
                errorID[3] = write_error[i]%16;

                // Skriver feilmelding til fil.
                const char *error_message = "Error message";
                char *error = convertErrorToChar(1, error_message, formatDateTimeToChar(calcDate, calcTime));
                writeToFile(file_error, errorID);
                // Resetter error melding når den er skrevet.
                write_error[i] = 0;
                i += 1;
            }
        }
        else{
            redLedOff();
        }
        
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
uint8_t getRemainingMinutes(unsigned long start, unsigned long duration){
    unsigned long current_time = getTime();
    unsigned long remaining_time_ms = (duration*60000) - (current_time - start);

    uint8_t remaining_seconds = remaining_time_ms/1000;
    uint8_t remaining_minutes = remaining_seconds/60;
    return remaining_minutes;
}

/**
 * @brief Henter ut gjenværende sekunder av forsøket når antall minutter er fratrukket
 * 
 * @param start Starttiden for forsøket
 * @param duration Lenget på forsøket i minutter
 * @return uint8_t Antall gjenværende sekunder av forsøket fratrukket minutter
 */
uint8_t getRemainingSeconds(unsigned long start, unsigned long duration){
    unsigned long current_time = getTime();
    unsigned long remaining_ms = duration - (current_time - start);
    uint8_t remaining_seconds = remaining_ms/1000;
    uint8_t remaining_seconds_removed_minutes = remaining_seconds%60;
    return remaining_seconds_removed_minutes;
}
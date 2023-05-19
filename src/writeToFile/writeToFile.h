#include <SD.h>
#include <stdio.h>
#include <string.h>
#include <Arduino.h>

/*
TODO:
[] Endre alle Serial.print til logging av feilkode i stedet
[] Bruke faktiske verdier for tid
*/

void createFile(char *headers, char *filename, bool is_error, uint8_t patient_id, uint8_t experiment_id);
char *createFileName(bool is_error, uint8_t patient_id, uint8_t experiment_id);
void writeToFile(char *filename, char *data);
void initSD();
uint8_t findNewExperimentId(void);
char *convertDataToChar(uint8_t temp_pcb, uint8_t temp_air, uint8_t temp_skin, uint8_t temp_led, const char *datetime);
char *convertErrorToChar(uint8_t error_code, const char *error_message, const char *datetime);
uint8_t checkIfFileExists(char *filename);
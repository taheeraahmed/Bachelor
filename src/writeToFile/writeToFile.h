#include <SD.h>
#include <stdio.h>

void createFile(char *headers, char *filename, bool is_error, uint8_t patient_id, uint8_t start_time);
char *createFileName(bool is_error, uint8_t patient_id, uint8_t start_time_buffer);
void writeToFile(char *filename, char *data);
void initSD();
char *convertDataToChar(uint8_t temp_pcb, uint8_t temp_air, uint8_t temp_skin, uint8_t temp_led, const char *datetime);
uint8_t checkIfFileExists(char *filename);
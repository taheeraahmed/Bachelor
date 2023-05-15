#include <SD.h>
#include <stdio.h>

uint8_t createFile(char *filename, char *headers);
uint8_t writeToFile(char *filename, const char *data);
char *createFileName(const char *patient_id, const char *datetime, bool is_error);
char *convertDataToChar(uint8_t temp_pcb, uint8_t temp_air, uint8_t temp_skin, uint8_t temp_led, const char *datetime);
#include <SD.h>
#include <stdio.h>

uint8_t createFile(char *headers, uint8_t start_time, bool is_error);
uint8_t writeToFile(char *filename, const char *data);
char *convertDataToChar(uint8_t temp_pcb, uint8_t temp_air, uint8_t temp_skin, uint8_t temp_led, const char *datetime);
#include <SD.h>
#include <stdio.h>

char temp_headers[] = "datetime, temp_pcb, temp_air, temp_skin, temp_led";
char error_headers[] = "datetime, error, error_msg";

uint8_t createFile(char* filename);
uint8_t writeToFile(char* filename, char* temp, char* datetime);
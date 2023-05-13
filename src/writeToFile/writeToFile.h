#include <SD.h>
#include <stdio.h>

uint8_t createFile(char *filename, char *headers);
uint8_t writeToFile(char *filename, const char *data);
char *createFileName(const char *patient_id, const char *datetime);
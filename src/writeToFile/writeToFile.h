#include <SD.h>
#include <stdio.h>

char filename[] = "text.txt";
File myFile;

uint8_t create_file(char* filename);
uint8_t write_to_file(char* filename, char* temp, char* datetime);
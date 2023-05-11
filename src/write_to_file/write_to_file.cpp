#include <stdio.h>

    

/**
 * @brief Function which writes temperatures and date to csv
 * @details The file is closed after the write is complete.
 * @param filename: Decieds which filename to create
 * @return 1: If the code has run successfully
*/
uint8_t create_file(char* filename){
	FILE *fp;
	fp = fopen(filename, "w+");
	fprintf(fp, "This is testing for fprintf...\n");
	fputs("datetime, temp_air, temp_pcb, temp_led, temp_skin", fp);
	fclose(fp);
    return 1;
}

/**
 * @brief Function which writes temperatures and date to csv
 * @details The file is closed after the write is complete.
 * @param filename: Decieds which filename to write to 
 * @param temp: The temperatures to be logged 
 * @param date: The timestamp of when the temperatures where taken
 * @return 1: If the code has run successfully
*/
uint8_t write_to_file(char* filename, char* temp, char* datetime){
	FILE *fp;
	fp = fopen(filename, "w+");
    fputs(datetime, fp);
	fputs(temp, fp);
	fclose(fp);
    return 1;
}
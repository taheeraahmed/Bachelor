#include "writeToFile/writeToFile.h"
#include "getTime/getTime.h"
#include <stdio.h>
#include <Arduino.h>

/*
TODO: Check if headers exists
*/

char temp_headers[50] = "datetime,temp_pcb,temp_air,temp_skin,temp_led";
char error_headers[50] = "datetime,error_code,error_msg";
uint8_t patient_id = 123;
uint8_t start_time = 0;

char *file_temp = createFileName(false, patient_id, start_time);
char *file_error = createFileName(true, patient_id, start_time);

void setup()
{
	Serial.begin(9600);
	Serial.println("Starting program..");
	initSD();
	createFile(temp_headers, file_temp, false, patient_id, start_time);
	createFile(error_headers, file_error, true, patient_id, start_time);
}
void loop()
{
	delay(6000);
}

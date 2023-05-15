#include "writeToFile/writeToFile.h"
#include "getTime/getTime.h"
#include <stdio.h>
#include <Arduino.h>

char temp_headers[50] = "datetime,temp_pcb,temp_air,temp_skin,temp_led";
char error_headers[50] = "datetime,error_code,error_msg";
const char *patient_id = "12345";
const char *start_time = "2021-05-05-12:00:00";
char *filename_log = createFileName(patient_id, start_time, false);
char *filename_error = createFileName(patient_id, start_time, true);

void setup()
{
	Serial.begin(9600);
	uint8_t create_file_temp = createFile(filename_log, temp_headers);
	uint8_t create_file_error = createFile(filename_error, error_headers);
	if (create_file_temp == 1 && create_file_error == 1)
	{
		Serial.println("File created successfully\n");
	}
	else
	{
		Serial.println("File creation failed\n");
	}
}
void loop()
{
	const char *data = convertDataToChar(23, 22, 21, 19, start_time);
	writeToFile("log1.csv", data);

	const char *error_data = "2021-05-05-12:00:00,1, Something went wrong :)";
	writeToFile("error1.csv", error_data);

	delay(3000);
}
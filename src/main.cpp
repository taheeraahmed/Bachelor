#include "writeToFile/writeToFile.h"
#include "getTime/getTime.h"
#include <stdio.h>
#include <Arduino.h>

char temp_headers[50] = "datetime,temp_pcb,temp_air,temp_skin,temp_led";
char error_headers[50] = "datetime,error_code,error_msg";
const char *patient_id = "12345";
uint8_t start_time = 0;

void setup()
{
	Serial.begin(9600);
	uint8_t create_file_temp = createFile(temp_headers, start_time, false);
	uint8_t create_file_error = createFile(error_headers, start_time, true);
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
	//const char *data = convertDataToChar(23, 22, 21, 19, start_time);
	//writeToFile("log1.csv", data);

	delay(3000);
}
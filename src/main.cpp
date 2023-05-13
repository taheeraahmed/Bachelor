#include "writeToFile/writeToFile.h"
#include "getTime/getTime.h"
#include <stdio.h>
#include <Arduino.h>

char temp_headers[50] = "datetime, temp_pcb, temp_air, temp_skin, temp_led";
char error_headers[50] = "datetime, error_code, error_msg";
const char *patient_id = "12345";
const char *datetime = "2021-05-05-12:00:00";
char *filename = createFileName(patient_id, datetime);

void setup()
{
	Serial.begin(9600);
	uint8_t create_file_temp = createFile(filename, temp_headers);
	if (create_file_temp == 1)
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
	const char *data = "2021-05-05-12:00:00, 22.3, 23.3, 12.2, 32.3\n";
	uint8_t write_to_file = writeToFile(filename, data);
	if (write_to_file == 1)
	{
		Serial.println("File written to successfully\n");
	}
	else
	{
		Serial.println("File write failed\n");
	}
	delay(3000);
}
#include "writeToFile/writeToFile.h"
#include <SD.h>
#include <string.h>
/**
 * @brief Function which creates a file, with a given filename and header
 * (for either temperatures or errors)
 * @details The file is closed after the write is complete.
 * @param filename: Decieds which filename to create
 * @param headers: The headers to be written to the file
 * @return 1: If the code has run successfully
 */
uint8_t createFile(char *filename, char *headers)
{
	if (!SD.begin(53))
	{
		Serial.println("SD card initialization failed! createFile");
		return 0;
	}
	Serial.println("SD card initialized successfully! createFile");
	File file;
	file = SD.open(filename, FILE_WRITE);
	if (file)
	{
		file.println(headers);
		file.close();
	}
	else
	{
		Serial.println("File creation failed");
		return 0;
	}
	return 1;
}

/**
 * @brief Function which writes temperatures and date to csv
 * @details The file is closed after the write is complete.
 * @param filename: Decieds which filename to write to
 * @param data: Could be both temperatures or errors to be logged
 * @param datetime: The timestamp of when the temperatures where taken
 * @return 1: If the code has run successfully
 */
uint8_t writeToFile(char *filename, const char *data)
{
	File file;

	file = SD.open(filename, FILE_WRITE);
	if (file)
	{
		file.println(data);
		Serial.println("File written to successfully");
		file.close();
		Serial.println("File closed successfully");
	}
	else
	{
		Serial.println("File not found! writeToFile");
		return 0;
	}
	return 1;
}

char *createFileName(const char *patient_id, const char *datetime, bool is_error)
{
	char *filename = new char[strlen(patient_id) + strlen("_") + strlen(datetime) + strlen(".csv") + 1];
	strcpy(filename, patient_id);
	strcat(filename, "/");
	strcat(filename, datetime);
	if (is_error)
	{
		strcat(filename, "_error");
	}
	strcat(filename, ".csv");
	return filename;
}

char *convertDataToChar(uint8_t temp_pcb, uint8_t temp_air, uint8_t temp_skin, uint8_t temp_led, const char *datetime)
{
	char *data = new char[strlen(datetime) + strlen(", ") + 4 * 4 + strlen("\n") + 1];
	strcpy(data, datetime);
	strcat(data, ", ");
	strcat(data, String(temp_pcb).c_str());
	strcat(data, ", ");
	strcat(data, String(temp_air).c_str());
	strcat(data, ", ");
	strcat(data, String(temp_skin).c_str());
	strcat(data, ", ");
	strcat(data, String(temp_led).c_str());
	return data;
}
#include "writeToFile/writeToFile.h"
#include <SD.h>
#include <string.h>

/**
 * @brief Function which creates a file, with a given filename and header
 * (for either temperatures or errors)
 * @details The file is closed after the write is complete.
 * @param headers: The headers to be written to the file
 * @param start_time: Used for creation of directory
 * @param is_error: Decides whether to create a file for errors or temperatures
 * @param patient_id: The patient id to be written to the filename
 * @return 1: If the code has run successfully
 */
uint8_t createFile(char *headers, uint8_t start_time, bool is_error, uint8_t patient_id)
{
	// Initialize SD card
	if (!SD.begin(53))
	{
		return 0;
	}
	// Convert start_time to char for directory name
	String start_time_str = String(start_time);
	const char *start_time_char = start_time_str.c_str();
	char start_time_buffer[20];
	strcpy(start_time_buffer, start_time_char);

	// Create directory
	if (!SD.mkdir(start_time_buffer))
	{
		Serial.println("Error creating directory!");
		return 0;
	}
	else
	{
		Serial.println("Directory created successfully!");
	}

	// Create a file given is_error, if is_error is true, then you create file called error.csv, otherwise call it log.csv and it should be
	// in the directory of the start_time it should also contain the patient id in the filename
	char filename[50];
	if (is_error)
	{
		strcpy(filename, start_time_buffer);
		strcat(filename, "/error_");
		strcat(filename, String(patient_id).c_str());
		strcat(filename, ".csv");
	}
	else
	{
		strcpy(filename, start_time_buffer);
		strcat(filename, "/log");
		strcat(filename, String(patient_id).c_str());
		strcat(filename, ".csv");
	}
	// Creating a file with the name
	File file = SD.open("filename.txt", FILE_WRITE);

	// If file is created successfully, write headers to file
	if (file)
	{
		Serial.println("File created successfully");
		file.println(headers);
		file.close();
	}
	else
	{
		Serial.println("File not created");
		return 0;
	}
	return 1;
}

/**
 * @brief Function which writes temperatures and date to csv
 * @details The file is closed after the write is complete.
 * @param filename: Decieds which filename to write to
 * @param data: Could be both temperatures or errors to be logged
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

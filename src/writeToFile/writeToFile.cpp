#include "writeToFile/writeToFile.h"
#include <SD.h>
#include <string.h>

uint8_t checkIfFileExists(char *filename)
{
	if (SD.exists(filename))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
 * @brief Function which initializes the SD card
 * @details The SD card is initialized on pin 53
 * @return void
 */
void initSD(){
	// Initialize SD card
	if (!SD.begin(53))
	{
		Serial.println("SD card initialization failed!");
	}
	else
	{
		Serial.println("SD card initialized successfully!");
	}
}

/**
 * @brief Function which creates a file
 * @details The file is closed after the write is complete.
 * @param headers: The headers to be written to the file
 * @param start_time: Used for creation of directory
 * @param is_error: Decides whether to create a file for errors or temperatures
 * @param patient_id: The patient id to be written to the filename
 * @return void
 */
void createFile(char *headers, char *filename, bool is_error, uint8_t patient_id, uint8_t start_time)
{
	// Convert start_time to char for directory name
	String start_time_str = String(start_time);
	const char *start_time_char = start_time_str.c_str();
	char start_time_buffer[20];
	strcpy(start_time_buffer, start_time_char);

	uint8_t file_exists = checkIfFileExists(filename);

	if(file_exists){
		Serial.println("File already exists");
		return;
	}
	else {
		// Create directory
		if (!SD.mkdir(start_time_buffer))
		{
			Serial.println("Error creating directory!");
		}
		else
		{
			Serial.println("Directory created successfully!");
		}

		// Creating a file with the name
		File file = SD.open(filename, FILE_WRITE);

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
			delete[] filename;
		};
	}
}

/**
 * @brief Function which creates a filename
 * @details The file is closed after the write is complete.
 * @param is_error: Decides whether to create a file for errors or temperatures
 * @param patient_id: The patient id to be written to the filename
 * @param start_time: Used for creation of directory
 * @return void
 */
char *createFileName(bool is_error, uint8_t patient_id, uint8_t start_time)
{
	// Convert start_time to char for directory name
	String start_time_str = String(start_time);
	const char *start_time_char = start_time_str.c_str();
	char start_time_buffer[20];
	strcpy(start_time_buffer, start_time_char);

	char *filename = new char[50];
	if (is_error)
	{
		strcpy(filename, start_time_buffer);
		strcat(filename, "/err_");
		strcat(filename, String(patient_id).c_str());
		strcat(filename, ".csv");
	}
	else
	{
		strcpy(filename, start_time_buffer);
		strcat(filename, "/log_");
		strcat(filename, String(patient_id).c_str());
		strcat(filename, ".csv");
	}
	return filename;
}

/**
 * @brief Function which writes temperatures and date to csv
 * @details The file is closed after the write is complete.
 * @param filename: Decieds which filename to write to
 * @param data: Could be both temperatures or errors to be logged
 * @return 1: If the code has run successfully
 */
void writeToFile(char *filename, char *data)
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
	}
	Serial.println("Write to file done");
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
